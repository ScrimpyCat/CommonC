if ARGV.count < 1
    puts 'Pass in SIMD size'
    exit
end

width = ARGV[0].to_i
type_sizes = []

4.times { |i| 
    if width / (8 << i) >= 2
        type_sizes << (8 << i)
    end
}

integer_type_units = ['s', 'u']
float_type_units = ['f']
type_units = ['s', 'u', 'f']

def types(units, sizes, width)
    units.map { |unit|
        sizes.filter{ |size|
            if unit == 'f'
                size >= 32
            else
                true
            end
        }.map { |size| "#{unit}#{size}x#{width / size}" }
    }.flatten
end

def to_integer_type(type)
    type.gsub('f', 'u')
end

def base(type)
    type[/.\d+/]
end

def base_size(type)
    type[/\d+/].to_i
end

def count(type)
    type[/\d+$/].to_i
end

def scalar(type)
    case type[0]
    when 's'
        "int#{base_size(type)}_t"
    when 'u'
        "uint#{base_size(type)}_t"
    when 'f'
        case base(type)
        when 'f32'
            'float'
        when 'f64'
            'double'
        end
    end
end

def scalar_readable(type)
    case type[0]
    when 's'
        'signed integer'
    when 'u'
        'unsigned integer'
    when 'f'
        'float'
    end
end

def format_word(word, value)
    case value.to_i
    when 1
        word[1]
    when 2
        word[0]
    when 4
        word[0]
    when 8
        word[1]
    when 16
        word[0]
    when 32
        word[0]
    when 64
        word[0]
    when 128
        word[1]
    when 256
        word[0]
    when 512
        word[0]
    when 1024
        word[1]
    end
end

def sequence(type, i: ->(i){ i }, pattern: 0, offset: 0, default: 0, start: 0, flt: 0, default_flt: 0)
    count(type).times.map { |index|
        value = nil
        convert = nil

        if (pattern == 0) || (((index + offset) % (pattern + 1)) != 0)
            value = i.is_a?(Proc) ? i.call(index + start) : i
            convert = flt
        else
            value = default
            convert = default_flt
        end

        if convert.is_a?(Float) && type[0] == 'f'
            value + convert
        else
            value
        end
    }
end

def sign(x)
    x >= 0 ? 1 : -1
end

def example_1(a, fmt, solve)
    "* @example #{fmt.call(a)} -> #{a.map { |arg| solve.call(arg)} }"
end

def example_1_custom(a, fmt, solve)
    "* @example #{fmt.call(a)} -> #{solve.call(a)}"
end

def example_2(a, b, fmt, solve)
    "* @example #{fmt.call(a, b)} -> #{a.zip(b).map { |args| solve.call(args[0], args[1])} }"
end

def example_3(a, b, c, fmt, solve)
    "* @example #{fmt.call(a, b, c)} -> #{a.zip(b, c).map { |args| solve.call(args[0], args[1], args[2])}}"
end

prev_unit = 's'
poly_type_defs = types(type_units, type_sizes, width).map { |type|
    defs = """
typedef struct { CCSimd_#{type} v[2]; } CCSimd_#{type}x2;
typedef struct { CCSimd_#{type} v[3]; } CCSimd_#{type}x3;
typedef struct { CCSimd_#{type} v[4]; } CCSimd_#{type}x4;
    """.strip

    if not type.start_with? prev_unit
        defs = "\n" + defs
        prev_unit = type[0]
    end

    defs
}.join("\n")

zero_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Initialise a vector with all zeroes.
 * @return The vector filled with zeroes.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdZero_#{type}(void);
    """.strip
}.join("\n\n")

fill_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Initialise a vector all elements set to @b v.
 * @param v The value to fill the vector with.
 * @return The filled vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdFill_#{type}(const #{scalar(type)} v);
    """.strip
}.join("\n\n")

load_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Load a vector from memory.
 * @param v The data to load into a vector.
 * @return The vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdLoad_#{type}(const #{scalar(type)} v[#{count(type)}]);
    """.strip
}.join("\n\n")

store_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Store a vector to memory.
 * @param dst A pointer to where the vector data should be stored.
 * @param src #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to store.
 */
static CC_FORCE_INLINE void CCSimdStore_#{type}(#{scalar(type)} dst[#{count(type)}], const CCSimd_#{type} src);
    """.strip
}.join("\n\n")

interleave_load_2_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Load 2 vectors from interleaved memory.
 * @param v The interleaved data to load into 2 vectors. Every [(index % 2) + 0] element will
 *          be loaded into poly vector[0], every [(index % 2) + 1] element will be loaded
 *          into poly vector[1].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_#{type}x2 CCSimdInterleaveLoad_#{type}x2(const #{scalar(type)} v[#{count(type) * 2}]);
    """.strip
}.join("\n\n")

interleave_load_3_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Load 3 vectors from interleaved memory.
 * @param v The interleaved data to load into 3 vectors. Every [(index % 3) + 0] element will
 *          be loaded into poly vector[0], every [(index % 3) + 1] element will be loaded
 *          into poly vector[1], every [(index % 3) + 2] element will be loaded into poly
 *          vector[2].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_#{type}x3 CCSimdInterleaveLoad_#{type}x3(const #{scalar(type)} v[#{count(type) * 3}]);
    """.strip
}.join("\n\n")

interleave_load_4_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Load 4 vectors from interleaved memory.
 * @param v The interleaved data to load into 4 vectors. Every [(index % 4) + 0] element will
 *          be loaded into poly vector[0], every [(index % 4) + 1] element will be loaded
 *          into poly vector[1], every [(index % 4) + 2] element will be loaded into poly
 *          vector[2], every [(index % 4) + 3] element will be loaded into poly vector[3].
 *
 * @return The poly vector with the loaded data.
 */
static CC_FORCE_INLINE CCSimd_#{type}x4 CCSimdInterleaveLoad_#{type}x4(const #{scalar(type)} v[#{count(type) * 4}]);
    """.strip
}.join("\n\n")

interleave_store_2_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Store 2 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Two #{count(type)} element vectors of #{base_size(type)}-bit #{scalar_readable(type)}s to store. Every poly
 *            vector[index % 2] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_#{type}x2(#{scalar(type)} dst[#{count(type) * 2}], const CCSimd_#{type}x2 src);
    """.strip
}.join("\n\n")

interleave_store_3_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Store 3 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Three #{count(type)} element vectors of #{base_size(type)}-bit #{scalar_readable(type)}s to store. Every poly
 *            vector[index % 3] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_#{type}x3(#{scalar(type)} dst[#{count(type) * 3}], const CCSimd_#{type}x3 src);
    """.strip
}.join("\n\n")

interleave_store_4_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Store 4 vectors by interleaving them into memory.
 * @param dst A pointer to where the interleaved vector data should be stored.
 * @param src Four #{count(type)} element vectors of #{base_size(type)}-bit #{scalar_readable(type)}s to store. Every poly
 *            vector[index % 4] will be stored at [index].
 */
static CC_FORCE_INLINE void CCSimdInterleaveStore_#{type}x4(#{scalar(type)} dst[#{count(type) * 4}], const CCSimd_#{type}x4 src);
    """.strip
}.join("\n\n")

get_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Get the element at @b index in vector @b a.
 * @param a The #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param index The index of the element to get.
 * @return The element.
 */
static CC_FORCE_INLINE #{scalar(type)} CCSimdGet_#{type}(const CCSimd_#{type} a, uint8_t index);
    """.strip
}.join("\n\n")

set_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Set the element to @b v at @b index in vector @b a.
 * @param a The #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param index The index of the element to set.
 * @param v The value to set the element to.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdSet_#{type}(const CCSimd_#{type} a, uint8_t index, #{scalar(type)} v);
    """.strip
}.join("\n\n")

set_sequence_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Set the elements specified to @b v in vector @b a.
 * @param a The #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param v The value to set the elements to.
 #{sequence(type, i: ->(i){ "* @param v#{i} Whether the element should be set (1) or not (0)." }).join("\n ")}
 * @return The set vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdSetSequence_#{type}(const CCSimd_#{type} a, #{scalar(type)} v, #{sequence(type, i: ->(i){ "_Bool v#{i}" }).join(', ')});
    """.strip
}.join("\n\n")

reinterpret_defs = types(type_units, type_sizes, width).map { |type|
    types(type_units, type_sizes, width).map { |to_type|
        """
/*!
 * @brief Reinterpret the vector @b a.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The reinterpreted vector.
 */
static CC_FORCE_INLINE CCSimd_#{to_type} CCSimd_#{to_type}_Reinterpret_#{type}(const CCSimd_#{type} a);
        """.strip
    }
}.flatten.join("\n\n")

cast_defs = types(type_units, type_sizes, width).map { |type|
    types(type_units, type_sizes, width).filter{ |to_type| count(to_type) == count(type) }.map { |to_type|
        """
/*!
 * @brief Cast the vector @b a.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The casted vector.
 */
static CC_FORCE_INLINE CCSimd_#{to_type} CCSimd_#{to_type}_Cast_#{type}(const CCSimd_#{type} a);
        """.strip
    }
}.flatten.join("\n\n")

not_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief NOT all elements of @b a.
 #{example_1(sequence(type, i: 1), ->(a){ "~#{a}" }, ->(a){ ~a })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the bitwise NOT.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdNot_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

and_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief AND all elements of @b a and @b b.
 #{example_2(sequence(type, i: 1), sequence(type,  i: 3), ->(a, b){ "#{a} & #{b}" }, ->(a, b){ a & b })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the AND'd result.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdAnd_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

and_not_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief AND all elements of NOT @b a and @b b.
 #{example_2(sequence(type, i: 1), sequence(type,  i: 3), ->(a, b){ "~#{a} & #{b}" }, ->(a, b){ ~a & b })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdAndNot_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

or_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief OR all elements of @b a and @b b.
 #{example_2(sequence(type, i: 1), sequence(type,  i: 2), ->(a, b){ "#{a} | #{b}" }, ->(a, b){ a | b })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the OR'd result.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdOr_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

or_not_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief OR all elements of NOT @b a and @b b.
 #{example_2(sequence(type, i: 1), sequence(type,  i: 2), ->(a, b){ "~#{a} | #{b}" }, ->(a, b){ ~a | b })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the result.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdOrNot_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

xor_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief XOR all elements of @b a and @b b.
 #{example_2(sequence(type, i: 1), sequence(type,  i: 3), ->(a, b){ "#{a} ^ #{b}" }, ->(a, b){ a ^ b })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the XOR'd result.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdXor_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

shift_left_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Left shift all elements of @b a by @b b.
 #{example_2(sequence(type, i: 1), sequence(type,  i: 3), ->(a, b){ "#{a} << #{b}" }, ->(a, b){ a << b })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdShiftLeft_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

shift_left_n_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Left shift all elements of @b a by @b n.
 #{example_1(sequence(type, i: 1), ->(a){ "#{a} << 3" }, ->(a){ a << 3 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdShiftLeftN_#{type}(const CCSimd_#{type} a, const uint8_t n);
    """.strip
}.join("\n\n")

shift_right_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Right#{type[0] == 's' ? ' arithmetic ' : ' '}shift all elements of @b a by @b b.
 #{example_2(sequence(type, i: 8), sequence(type,  i: 3), ->(a, b){ "#{a} >> #{b}" }, ->(a, b){ a >> b })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdShiftRight_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

shift_right_n_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Right#{type[0] == 's' ? ' arithmetic ' : ' '}shift all elements of @b a by @b n.
 #{example_1(sequence(type, i: 8), ->(a){ "#{a} >> 3" }, ->(a){ a >> 3 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param n The number of bits to shift the vector elements by.
 * @return The vector representing the shifted result.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdShiftRightN_#{type}(const CCSimd_#{type} a, const uint8_t n);
    """.strip
}.join("\n\n")

rotate_left_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Left rotate all elements of @b a by @b b.
 #{example_2(sequence(type, i: 1), sequence(type,  i: 3), ->(a, b){ "#{a} rol #{b}" }, ->(a, b){ 8 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdRotateLeft_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

rotate_left_n_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Left rotate all elements of @b a by @b n.
 #{example_1(sequence(type, i: 1), ->(a){ "#{a} rol 3" }, ->(a){ 8 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdRotateLeftN_#{type}(const CCSimd_#{type} a, const uint8_t n);
    """.strip
}.join("\n\n")

rotate_right_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Right rotate all elements of @b a by @b b.
 #{example_2(sequence(type, i: 8), sequence(type,  i: 3), ->(a, b){ "#{a} ror #{b}" }, ->(a, b){ 1 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdRotateRight_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

rotate_right_n_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Right rotate all elements of @b a by @b n.
 #{example_1(sequence(type, i: 8), ->(a){ "#{a} ror 3" }, ->(a){ 1 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param n The number of bits to rotate the vector elements by.
 * @return The vector representing the rotated result.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdRotateRightN_#{type}(const CCSimd_#{type} a, const uint8_t n);
    """.strip
}.join("\n\n")

lowest_unset_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Finds lowest unset bit of all elements of @b a.
 #{example_1(sequence(type, pattern: 1, i: 2, default: 1), ->(a){ "#{a}" }, ->(a){ 3 - a })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the lowest unset bit.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdLowestUnset_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

lowest_set_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Finds lowest set bit of all elements of @b a.
 #{example_1(sequence(type, pattern: 1, i: 6, default: 5), ->(a){ "#{a}" }, ->(a){ a & 3 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the lowest set bit.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdLowestSet_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

highest_set_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Finds highest set bit of all elements of @b a.
 #{example_1(sequence(type, pattern: 1, i: 1, default: 3), ->(a){ "#{a}" }, ->(a){ ((a / 3) * 1) + 1 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the highest set bit.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdHighestSet_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

next_pow_2_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Finds the minimum power of 2 that can hold each element of @b a.
 #{example_1(sequence(type, pattern: 1, i: 1, default: 3), ->(a){ "#{a}" }, ->(a){ ((a / 3) * 3) + 1 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the next power of 2.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdNextPow2_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

mask_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Creates a mask for the entire values range for each element of @b a.
 #{example_1(sequence(type, pattern: 1, i: 1, default: 2), ->(a){ "#{a}" }, ->(a){ ((a - 1) * 2) + 1 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdMask_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

mask_lower_pow_2_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Creates a mask for lower bits of a power of 2 value for each element of @b a.
 #{example_1(sequence(type, pattern: 1, i: 2, default: 4), ->(a){ "#{a}" }, ->(a){ a - 1 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdMaskLowerPow2_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

mask_highest_unset_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Creates a mask for the entire range of unset bits after the highest set bit for
 *        each element of @b a.
 *
 #{example_1(sequence(type, pattern: 1, i: 2, default: 1), ->(a){ "#{a}" }, ->(a){ a * -2 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the mask.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdMaskHighestUnset_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

count_lowest_unset_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Count the trailing zero bits of all elements of @b a.
 #{example_1(sequence(type, start: 1), ->(a){ "#{a}" }, ->(a){ (a & -a).bit_length - 1 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the number of trailing zero bits.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdCountLowestUnset_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

count_highest_unset_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Count the leading zero bits of all elements of @b a.
 #{example_1(sequence(type, start: 1), ->(a){ "#{a}" }, ->(a){ base_size(type) - a.bit_length })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the number of leading zero bits.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdCountHighestUnset_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

count_set_defs = types(integer_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Count the set bits of all elements of @b a.
 #{example_1(sequence(type, pattern: 1, i: 2, default: 3), ->(a){ "#{a}" }, ->(a){ a.to_s(2).count('1') })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the number of set bits.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdCountSet_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

compare_equal_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 #{example_2(sequence(type, start: 1, flt: 0.5), sequence(type, pattern: 1, start: 1, flt: 0.5), ->(a, b){ "#{a} == #{b}" }, ->(a, b){ (a == b ? 1 : 0) * sign(a) })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdCompareEqual_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

mask_compare_equal_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compare if all elements of @b a are equal to @b b.
 #{example_2(sequence(type, start: 1, flt: 0.5), sequence(type, pattern: 1, start: 1, flt: 0.5), ->(a, b){ "#{a} == #{b}" }, ->(a, b){ a == b ? -1 : 0 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_#{to_integer_type(type)} CCSimdMaskCompareEqual_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

compare_not_equal_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 #{example_2(sequence(type, start: 1, flt: 0.5), sequence(type, pattern: 1, start: 1, flt: 0.5), ->(a, b){ "#{a} != #{b}" }, ->(a, b){ (a != b ? 1 : 0) * sign(a) })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdCompareNotEqual_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

mask_compare_not_equal_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compare if all elements of @b a are not equal to @b b.
 #{example_2(sequence(type, start: 1, flt: 0.5), sequence(type, pattern: 1, start: 1, flt: 0.5), ->(a, b){ "#{a} != #{b}" }, ->(a, b){ a != b ? -1 : 0 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_#{to_integer_type(type)} CCSimdMaskCompareNotEqual_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

compare_less_than_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compare if all elements of @b a are less than @b b.
 #{example_2(sequence(type, flt: 0.5), sequence(type, i: ->(i){ i * 2 }, flt: 0.5), ->(a, b){ "#{a} < #{b}" }, ->(a, b){ (a < b ? 1 : 0) * sign(a) })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdCompareLessThan_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

mask_compare_less_than_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compare if all elements of @b a are less than @b b.
 #{example_2(sequence(type, flt: 0.5), sequence(type, i: ->(i){ i * 2 }, flt: 0.5), ->(a, b){ "#{a} < #{b}" }, ->(a, b){ a < b ? -1 : 0 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_#{to_integer_type(type)} CCSimdMaskCompareLessThan_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

compare_less_than_equal_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 #{example_2(sequence(type, flt: 0.5), sequence(type, i: ->(i){ i * 2 }, flt: 0.5), ->(a, b){ "#{a} <= #{b}" }, ->(a, b){ (a <= b ? 1 : 0) * sign(a) })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdCompareLessThanEqual_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

mask_compare_less_than_equal_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compare if all elements of @b a are less than or equal to @b b.
 #{example_2(sequence(type, flt: 0.5), sequence(type, i: ->(i){ i * 2 }, flt: 0.5), ->(a, b){ "#{a} <= #{b}" }, ->(a, b){ a <= b ? -1 : 0 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_#{to_integer_type(type)} CCSimdMaskCompareLessThanEqual_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

compare_greater_than_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 #{example_2(sequence(type, start: 1, flt: 0.5), sequence(type, pattern: 1, start: 1, flt: 0.5), ->(a, b){ "#{a} > #{b}" }, ->(a, b){ (a > b ? 1 : 0) * sign(a) })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdCompareGreaterThan_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

mask_compare_greater_than_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compare if all elements of @b a are greater than @b b.
 #{example_2(sequence(type, start: 1, flt: 0.5), sequence(type, pattern: 1, start: 1, flt: 0.5), ->(a, b){ "#{a} > #{b}" }, ->(a, b){ a > b ? -1 : 0 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_#{to_integer_type(type)} CCSimdMaskCompareGreaterThan_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

compare_greater_than_equal_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 #{example_2(sequence(type, start: 1, flt: 0.5), sequence(type, pattern: 1, start: 1, flt: 0.5), ->(a, b){ "#{a} >= #{b}" }, ->(a, b){ (a >= b ? 1 : 0) * sign(a) })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdCompareGreaterThanEqual_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

mask_compare_greater_than_equal_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compare if all elements of @b a are greater than or equal to @b b.
 #{example_2(sequence(type, start: 1, flt: 0.5), sequence(type, pattern: 1, start: 1, flt: 0.5), ->(a, b){ "#{a} >= #{b}" }, ->(a, b){ a >= b ? -1 : 0 })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to compare.
 * @return The vector with the result of the comparison.
 */
static CC_FORCE_INLINE CCSimd_#{to_integer_type(type)} CCSimdMaskCompareGreaterThanEqual_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

add_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Add all elements of @b a and @b b.
 #{example_2(sequence(type, start: 1, flt: 0.5), sequence(type, start: 1, i: ->(i){ i / 2 }, flt: 0.0), ->(a, b){ "#{a} + #{b}" }, ->(a, b){ a + b })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s as the addend.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s as the addend.
 * @return The vector representing the sum.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdAdd_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

sub_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Subtract all elements of @b b from @b a.
 #{example_2(sequence(type, start: 1, flt: 0.5), sequence(type, start: 1, i: ->(i){ i / 2 }, flt: 0.0), ->(a, b){ "#{a} - #{b}" }, ->(a, b){ a - b })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s as the minuend.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s as the subtrahend.
 * @return The vector representing the difference.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdSub_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

mul_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Multiply all elements of @b a by @b b.
 #{example_2(sequence(type, start: 1, flt: 0.5), sequence(type, flt: 0.0), ->(a, b){ "#{a} * #{b}" }, ->(a, b){ a * b })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s as the multiplier.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s as the multiplicand.
 * @return The vector representing the product.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdMul_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

madd_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Multiply all elements of @b a by @b b and add all elements of @b c.
 * @description (a * b) + c
 #{example_3(sequence(type, flt: 0.5), sequence(type, i: 2, flt: 0.0), sequence(type, i: 1, flt: 0.0), ->(a, b, c){ "(#{a} * #{b}) + #{c}" }, ->(a, b, c){ (a * b) + c })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to multiply.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to multiply.
 * @param c #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to add.
 * @return The vector representing the multiply and add.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdMadd_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b, const CCSimd_#{type} c);
    """.strip
}.join("\n\n")

neg_madd_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Multiply and negate all elements of @b a by @b b and add all elements of @b c.
 * @description -(a * b) + c
 #{example_3(sequence(type, flt: 0.5), sequence(type, i: 2, flt: 0.0), sequence(type, i: 1, flt: 0.0), ->(a, b, c){ "-(#{a} * #{b}) + #{c}" }, ->(a, b, c){ -(a * b) + c })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to multiply.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to multiply.
 * @param c #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to add.
 * @return The vector representing the negated multiply and add.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdNegMadd_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b, const CCSimd_#{type} c);
    """.strip
}.join("\n\n")

msub_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Multiply all elements of @b a by @b b and subtract all elements of @b c.
 * @description (a * b) - c
 #{example_3(sequence(type, flt: 0.5), sequence(type, i: 2, flt: 0.0), sequence(type, i: 1, flt: 0.0), ->(a, b, c){ "(#{a} * #{b}) - #{c}" }, ->(a, b, c){ (a * b) - c })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to multiply.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to multiply.
 * @param c #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to subtract.
 * @return The vector representing the multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdMsub_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b, const CCSimd_#{type} c);
    """.strip
}.join("\n\n")

neg_msub_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Multiply and negate all elements of @b a by @b b and sub all elements of @b c.
 * @description -(a * b) - c
 #{example_3(sequence(type, flt: 0.5), sequence(type, i: 2, flt: 0.0), sequence(type, i: 1, flt: 0.0), ->(a, b, c){ "-(#{a} * #{b}) - #{c}" }, ->(a, b, c){ -(a * b) - c })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to multiply.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to multiply.
 * @param c #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to subtract.
 * @return The vector representing the negated multiply and subtract.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdNegMsub_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b, const CCSimd_#{type} c);
    """.strip
}.join("\n\n")

div_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Divide all elements of @b a by @b b.
 #{example_2(sequence(type, start: 1, flt: 0.5), sequence(type, i: 2, flt: 0.0), ->(a, b){ "#{a} / #{b}" }, ->(a, b){ a / b })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s as the dividend.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s as the divisor.
 * @return The vector representing the quotient.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdDiv_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

mod_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Modulo of all elements of @b a by @b b.
 #{example_2(sequence(type, start: 1, flt: 0.5), sequence(type, i: 2, flt: 0.0), ->(a, b){ "#{a} % #{b}" }, ->(a, b){ a % b })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s as the dividend.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s as the divisor.
 * @return The vector representing the remainder.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdMod_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

round_nearest_away_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Round all elements to nearest with halves away from zero.
 #{example_1(sequence(type, i: ->(a){ a + 1.5 }), ->(a){ "#{a}" }, ->(a){ a.round(half: :up) })}
 #{example_1(sequence(type, i: ->(a){ -(a + 1.5) }), ->(a){ "#{a}" }, ->(a){ a.round(half: :up) })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdRoundNearestAway_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

round_nearest_even_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Round all elements to nearest with halves to even.
 #{example_1(sequence(type, i: ->(a){ a + 1.5 }), ->(a){ "#{a}" }, ->(a){ a.round(half: :even) })}
 #{example_1(sequence(type, i: ->(a){ -(a + 1.5) }), ->(a){ "#{a}" }, ->(a){ a.round(half: :even) })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdRoundNearestEven_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

round_zero_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Round all elements to zero.
 #{example_1(sequence(type, i: ->(a){ a + 1.5 }), ->(a){ "#{a}" }, ->(a){ a.round(half: :down) })}
 #{example_1(sequence(type, i: ->(a){ -(a + 1.5) }), ->(a){ "#{a}" }, ->(a){ a.round(half: :down) })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdRoundZero_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

floor_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Round all elements down.
 #{example_1(sequence(type, i: ->(a){ a + 1.5 }), ->(a){ "#{a}" }, ->(a){ a.floor })}
 #{example_1(sequence(type, i: ->(a){ -(a + 1.5) }), ->(a){ "#{a}" }, ->(a){ a.floor })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdFloor_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

ceil_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Round all elements up.
 #{example_1(sequence(type, i: ->(a){ a + 1.5 }), ->(a){ "#{a}" }, ->(a){ a.ceil })}
 #{example_1(sequence(type, i: ->(a){ -(a + 1.5) }), ->(a){ "#{a}" }, ->(a){ a.ceil })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The rounded vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdCeil_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

hadd_defs = types(type_units, type_sizes, width).map { |type|
    input = sequence(type, start: 1, flt: 0.5)
    """
/*!
 * @brief Horizontally add the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 #{example_1(input, ->(a){ "#{a}.(CC_SIMD_LANE_MASK(#{sequence(type).join(', ')}), #{sequence(type, i: 0)[0..-2].join(', ')})" }, ->(a){ a == input[0] ? input.sum : :undefined }).gsub(':', '')}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to horizontally add.
 #{sequence(type, i: ->(i){ "* @param v#{i} The lane mask to indicate the horizontal add to store in [#{i}]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the\n *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).\n *" }).join("\n ")}
 * @return The horizontally added vector elements.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdHadd_#{type}(const CCSimd_#{type} a, #{sequence(type, i: ->(i){ "uint8_t v#{i}" }).join(', ')});
    """.strip
}.join("\n\n")

hsub_defs = types(type_units, type_sizes, width).map { |type|
    input = sequence(type, start: 1, flt: 0.5)
    input[0] = input.sum
    """
/*!
 * @brief Horizontally subtract the elements of a vector.
 * @description Can selectively decide which elements are the sum of which other elements.
 #{example_1(input, ->(a){ "#{a}.(CC_SIMD_LANE_MASK(#{sequence(type).join(', ')}), #{sequence(type, i: 0)[0..-2].join(', ')})" }, ->(a){ a == input[0] ? a - input.drop(1).sum : :undefined }).gsub(':', '')}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to horizontally subtract.
 #{sequence(type, i: ->(i){ "* @param v#{i} The lane mask to indicate the horizontal subtract to store in [#{i}]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the\n *           elements that should be subtracted together, or use 0 to do nothing (the value stored will be undefined).\n *" }).join("\n ")}
 * @return The horizontally subtracted vector elements.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdHsub_#{type}(const CCSimd_#{type} a, #{sequence(type, i: ->(i){ "uint8_t v#{i}" }).join(', ')});
    """.strip
}.join("\n\n")

dot_defs = types(type_units, type_sizes, width).map { |type|
    input = sequence(type, start: 1, flt: 0.5)
    """
/*!
 * @brief Calculate the dot product of elements from vector @b a and @b b.
 * @description Can selectively decide which elements are used to calculate the dot product.
 #{example_2(input, sequence(type, i: 2), ->(a, b){ "#{a}x#{b}.(CC_SIMD_LANE_MASK(#{sequence(type).join(', ')}), #{sequence(type, i: 0)[0..-2].join(', ')})" }, ->(a, b){ a == input[0] ? input.map { |i| i * b }.sum : :undefined }).gsub(':', '')}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to use for the dot product.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to use for the dot product.
 #{sequence(type, i: ->(i){ "* @param v#{i} The lane mask to indicate the dot product to store in [#{i}]. Use @b CC_SIMD_LANE_MASK with the simd lane numbers to specify the\n *           elements that should be added together, or use 0 to do nothing (the value stored will be undefined).\n *" }).join("\n ")}
 * @return The resulting vector elements of the dot product.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdDot_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b, #{sequence(type, i: ->(i){ "uint8_t v#{i}" }).join(', ')});
    """.strip
}.join("\n\n")

sum_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Sum the elements of @b a.
 #{example_1_custom(sequence(type, start: 1, flt: 0.5), ->(a){ "#{a}" }, ->(a){ a.sum })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to sum.
 * @return The sum.
 */
static CC_FORCE_INLINE #{scalar(type)} CCSimdSum_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

neg_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Negate each element in @b a.
 #{example_1(sequence(type, start: 1, flt: 0.5), ->(a){ "-#{a}" }, ->(a){ -a })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to negate.
 * @return The negated vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdNeg_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

abs_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Absolute each element in @b a.
 #{example_1(sequence(type, start: 1, flt: 0.5), ->(a){ "-#{a}" }, ->(a){ a.abs })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to get the absolute of.
 * @return The absolute vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdAbs_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

min_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Get the min of each element from @b a and @b b.
 #{example_2(sequence(type, start: 1, flt: 0.0).zip(sequence(type, i: 10, pattern: 1, flt: 0.0)).map { |args| args[1] != 0 ? args[0] * args[1] : args[0] }, sequence(type, start: 1, flt: 0.5).zip(sequence(type, i: 10, pattern: 1, offset: 1, flt: 0.5)).map { |args| args[1] != 0 ? args[0] * args[1] : args[0] }, ->(a, b){ "min(#{a}, #{b})" }, ->(a, b){ a < b ? a : b })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the minimum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdMin_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

max_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Get the max of each element from @b a and @b b.
 #{example_2(sequence(type, start: 1, flt: 0.0).zip(sequence(type, i: 10, pattern: 1, flt: 0.0)).map { |args| args[1] != 0 ? args[0] * args[1] : args[0] }, sequence(type, start: 1, flt: 0.5).zip(sequence(type, i: 10, pattern: 1, offset: 1, flt: 0.5)).map { |args| args[1] != 0 ? args[0] * args[1] : args[0] }, ->(a, b){ "max(#{a}, #{b})" }, ->(a, b){ a > b ? a : b })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s.
 * @return The vector representing the maximum of the two vectors.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdMax_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b);
    """.strip
}.join("\n\n")

clamp_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Clamp each element of vector @b a between the min and max vectors.
 #{example_3(sequence(type, start: 1, flt: 0.5), sequence(type, i: 2, flt: 0.0), sequence(type, i: 3, flt: 0.0), ->(a, b, c){ "clamp(#{a}, #{b}, #{c})" }, ->(a, b, c){ (a < b ? b : (a > c ? c : a)) })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to be clamped.
 * @param min #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to use as the minimum.
 * @param max #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to use as the maximum.
 * @return The clamped vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdClamp_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} min, const CCSimd_#{type} max);
    """.strip
}.join("\n\n")

sqrt_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the square root of each element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to get the square root of.
 * @return The square root vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdSqrt_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

inv_sqrt_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the reciprocal square root of each element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to get the inverse square root of.
 * @return The inverse square root vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdInvSqrt_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

cbrt_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the cube root of each element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to get the cube root of.
 * @return The cube root vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdCbrt_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

inv_cbrt_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the reciprocal cube root of each element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to get the inverse cube root of.
 * @return The inverse cube root vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdInvCbrt_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

pow_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute value of each element in the vector @b Base raised by vector @b Exponent.
 * @param Base #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to be raised.
 * @param Exponent #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdPow_#{type}(const CCSimd_#{type} Base, const CCSimd_#{type} Exponent);
    """.strip
}.join("\n\n")

pow_2_defs = types(type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Computes 2^trunc(n) for each element raised by vector @b Exponent.
 * @param Exponent #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdPow2_#{type}(const CCSimd_#{type} Exponent);
    """.strip
}.join("\n\n")

exp_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Computes e^n (Euler's number 2.7182818..) for each element raised by vector @b a.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdExp_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

exp_2_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Computes 2^n for each element raised by vector @b a.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to raise.
 * @return The raised vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdExp2_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

log_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Computes base e logarithm for each element in vector @b a.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to log.
 * @return The log vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdLog_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

log_2_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Computes base 2 logarithm for each element in vector @b a.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to log.
 * @return The log vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdLog2_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")


sin_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the sine of each radian element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)} radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdSin_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

pos_sin_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the sine of each positive radian element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)} radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdPosSin_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

pi_rad_sin_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the sine of each -pi to pi (-180° to 180°) radian element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)} radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdPiRadSin_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

pos_pi_rad_sin_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the sine of each 0 to pi (0° to 180°) radian element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)} radians.
 * @return The sine vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdPosPiRadSin_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

arc_sin_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the arc sine of each element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}.
 * @return The arc sine vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdArcSin_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

half_pi_rad_cos_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the cosine of each -pi/2 to pi/2 (-90° to 90°) radian element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)} radians.
 * @return The cosine vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdHalfPiRadCos_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

cos_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the cosine of each radian element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)} radians.
 * @return The cosine vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdCos_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

arc_cos_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the arc cosine of each element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}.
 * @return The arc cosine vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdArcCos_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

tan_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the tangent of each radian element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)} radians.
 * @return The tangent vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdTan_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

qtr_pi_arc_tan_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the arc tangent of each -tan(pi/4) to tan(pi/4) (-1 to 1) element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}.
 * @return The arc tangent vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdQtrPiArcTan_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

arc_tan_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the arc tangent of each element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}.
 * @return The arc tangent vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdArcTan_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

arc_tan_2_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the arc tangent of y / x of each element in the vector.
 * @note When @b CC_SIMD_ARCTAN2_PRINCIPAL is defined the range (-pi, pi] is used, otherwise the default
 *       uses [-pi, pi]. By default when x and y are 0 the result is undefined, if @b CC_SIMD_ARCTAN2_UNDEFINED_AS_ZERO
 *       is defined 0.0 is returned, or @b CC_SIMD_ARCTAN2_UNDEFINED can be defined to the desired return value.
 *
 * @param y #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}.
 * @param x #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}.
 * @return The arc tangent vector of y / x.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdArcTan2_#{type}(const CCSimd_#{type} y, const CCSimd_#{type} x);
    """.strip
}.join("\n\n")

csc_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the cosecant (reciprocal sine) of each radian element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)} radians.
 * @return The cosecant vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdCsc_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

sec_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the secant (reciprocal cosine) of each radian element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)} radians.
 * @return The secant vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdSec_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

cot_defs = types(float_type_units, type_sizes, width).map { |type|
    """
/*!
 * @brief Compute the cotangent (reciprocal tangent) of each radian element in the vector.
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)} radians.
 * @return The cotangent vector.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdCot_#{type}(const CCSimd_#{type} a);
    """.strip
}.join("\n\n")

swizzle_defs = types(type_units, type_sizes, width).map { |type|
    values = sequence(type, start: 1, i: ->(i){ i * 10 })
    """
/*!
 * @brief Swizzle the elements of @b a.
 * @description The same element can be repeated.
 #{example_2(values, sequence(type).reverse, ->(a, b){ "#{a}.(#{b.join(', ')})" }, ->(a, b){ values[b] })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to swizzle.
 #{sequence(type, i: ->(i){ "* @param v#{i} The index of the element in @b a to be moved to [#{i}]." }).join("\n ")}
 * @return The rearranged vector elements.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdSwizzle_#{type}(const CCSimd_#{type} a, #{sequence(type, i: ->(i){ "uint8_t v#{i}" }).join(', ')});
    """.strip
}.join("\n\n")

interleave_defs = types(type_units, type_sizes, width).map { |type|
    values_a = sequence(type, start: 1)
    values_b = sequence(type, start: 1, i: ->(i){ i * 10 })
    """
/*!
 * @brief Interleave the elements of @b a and @b b.
 #{example_3(values_a, values_b, sequence(type, pattern: 1, i: 1), ->(a, b, c){ "#{a}x#{b}.(#{c.join(', ')})" }, ->(a, b, c){ c == 1 ? b : a })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to interleave.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to interleave.
 #{sequence(type, i: ->(i){ "* @param v#{i} The index of the vector argument to include the element from. Use 0 for @b a and 1 for @b b." }).join("\n ")}
 * @return The interleaved vector elements.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdInterleave_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b, #{sequence(type, i: ->(i){ "uint8_t v#{i}" }).join(', ')});
    """.strip
}.join("\n\n")

merge_defs = types(type_units, type_sizes, width).map { |type|
    values_a = sequence(type, start: 1)
    values_b = sequence(type, start: 1, i: ->(i){ i * 10 })
    """
/*!
 * @brief Merge the elements of @b a and @b b.
 * @description A merge combines the functionality of a swizzle and interleave.
 #{example_3(values_a, values_b, sequence(type, pattern: 1, i: 1), ->(a, b, c){ "#{a}x#{b}.(#{c.map{ |i| ['CC_SIMD_A1', 'CC_SIMD_B1'][i] }.join(', ')})" }, ->(a, b, c){ c == 1 ? values_b[1] : values_a[1] })}
 * @param a #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to merge.
 * @param b #{format_word(['A', 'An'], count(type))} #{count(type)} element vector of #{base_size(type)}-bit #{scalar_readable(type)}s to merge.
 #{sequence(type, i: ->(i){ "* @param v#{i} The vector element argument to be moved to [#{i}]. Use CC_SIMD_An or CC_SIMD_Bn to select the vector and element." }).join("\n ")}
 * @return The merged vector elements.
 */
static CC_FORCE_INLINE CCSimd_#{type} CCSimdMerge_#{type}(const CCSimd_#{type} a, const CCSimd_#{type} b, #{sequence(type, i: ->(i){ "uint8_t v#{i}" }).join(', ')});
    """.strip
}.join("\n\n")

element_types = [{}, {}]
2.times { |i|
    types([integer_type_units, float_type_units][i], type_sizes, width).each { |type|
        macro = element_types[i][count(type)]
        if macro
            macro << ", \\\n"
        else
            macro = "#define CC_SIMD_#{width}_#{count(type)}_ELEMENT_#{['INTEGER', 'FLOAT'][i]}_TYPES \\\n"
            element_types[i][count(type)] = macro
        end

        macro << "(#{base(type)}, #{count(type)})"
    }
}

unsigned_types = types(['u'], type_sizes.reverse, width).map { |type| "(#{base(type)}, #{count(type)})" }

signed_types = types(['s', 'f'], type_sizes.reverse, width).map { |type| "(#{base(type)}, #{count(type)})" }

mixed_element_types = {}
types(['s', 'f'], type_sizes, width).each { |type|
    macro = mixed_element_types[count(type)]
    if macro
        macro << ", \\\n"
    else
        macro = "#define CC_SIMD_#{width}_#{count(type)}_ELEMENT_TYPES \\\n"
        mixed_element_types[count(type)] = macro
    end

    macro << "CC_SIMD_#{width}_#{count(type)}_ELEMENT_#{['INTEGER', 'FLOAT'][type[0] == 'f' ? 1 : 0]}_TYPES"
}

all_types = mixed_element_types.sort.reverse.map { |args| "CC_SIMD_#{width}_#{args[0]}_ELEMENT_TYPES" }

all_integer_types = types(['s'], type_sizes, width).map { |type| "CC_SIMD_#{width}_#{count(type)}_ELEMENT_INTEGER_TYPES" }

all_float_types = types(['f'], type_sizes, width).map { |type| "CC_SIMD_#{width}_#{count(type)}_ELEMENT_FLOAT_TYPES" }

all_integer_bit_types = types(integer_type_units, type_sizes, width).map { |args| "#define CC_SIMD_#{width}_INTEGER_#{base_size(args)}_TYPES CC_SIMD_#{width}_#{count(args)}_ELEMENT_INTEGER_TYPES" }.uniq.reverse

puts """
#ifndef CommonC_Simd#{width}_h
#define CommonC_Simd#{width}_h

#include <CommonC/Extensions.h>
#include <CommonC/Platform.h>
#include <CommonC/Assertion.h>
#include <CommonC/Maths.h>
#include <CommonC/BitTricks.h>

#if CC_HARDWARE_VECTOR_SUPPORT_ARM_NEON
#include <CommonC/Simd#{width}Types_arm.h>
#endif


#{poly_type_defs}


#pragma mark - Setting and Getting
#pragma mark Zero

#{zero_defs}


#pragma mark Fill

#{fill_defs}


#pragma mark Load

#{load_defs}


#pragma mark Store

#{store_defs}


#pragma mark Interleaved Loads
#pragma mark 2 Vector Interleaved Load

#{interleave_load_2_defs}


#pragma mark 3 Vector Interleaved Load

#{interleave_load_3_defs}


#pragma mark 4 Vector Interleaved Load

#{interleave_load_4_defs}


#pragma mark Interleaved Stores
#pragma mark 2 Vector Interleaved Store

#{interleave_store_2_defs}


#pragma mark 3 Vector Interleaved Store

#{interleave_store_3_defs}


#pragma mark 4 Vector Interleaved Store

#{interleave_store_4_defs}


#pragma mark Get Element

#{get_defs}


#pragma mark Set Element

#{set_defs}


#pragma mark Set Sequence

#{set_sequence_defs}


#pragma mark - Types
#pragma mark Reinterpret

#{reinterpret_defs}


#pragma mark Cast

#{cast_defs}


#pragma mark - Bitwise Operations
#pragma mark Not

#{not_defs}


#pragma mark And

#{and_defs}


#pragma mark And Not

#{and_not_defs}


#pragma mark Or

#{or_defs}


#pragma mark Or Not

#{or_not_defs}


#pragma mark Xor

#{xor_defs}


#pragma mark Shift Left

#{shift_left_defs}


#pragma mark Shift Left N

#{shift_left_n_defs}


#pragma mark Shift Right

#{shift_right_defs}


#pragma mark Shift Right N

#{shift_right_n_defs}


#pragma mark Rotate Left

#{rotate_left_defs}


#pragma mark Rotate Left N

#{rotate_left_n_defs}


#pragma mark Rotate Right

#{rotate_right_defs}


#pragma mark Rotate Right N

#{rotate_right_n_defs}


#pragma mark - Bit Maths
#pragma mark Lowest Unset Bits

#{lowest_unset_defs}


#pragma mark Lowest Set Bits

#{lowest_set_defs}


#pragma mark Highest Set Bits

#{highest_set_defs}


#pragma mark Next Power of 2

#{next_pow_2_defs}


#pragma mark Mask Value

#{mask_defs}


#pragma mark Mask Lower Power of 2

#{mask_lower_pow_2_defs}


#pragma mark Mask Highest Unset Value

#{mask_highest_unset_defs}


#pragma mark Count Trailing Zero Bits

#{count_lowest_unset_defs}


#pragma mark Count Leading Zero Bits

#{count_highest_unset_defs}


#pragma mark Count Set Bits

#{count_set_defs}


#pragma mark - Comparisons
#pragma mark Equal

#{compare_equal_defs}


#pragma mark Masked Equal

#{mask_compare_equal_defs}


#pragma mark Not Equal

#{compare_not_equal_defs}


#pragma mark Masked Not Equal

#{mask_compare_not_equal_defs}


#pragma mark Less Than

#{compare_less_than_defs}


#pragma mark Masked Less Than

#{mask_compare_less_than_defs}


#pragma mark Less Than Or Equal

#{compare_less_than_equal_defs}


#pragma mark Masked Less Than Or Equal

#{mask_compare_less_than_equal_defs}


#pragma mark Greater Than

#{compare_greater_than_defs}


#pragma mark Masked Greater Than

#{mask_compare_greater_than_defs}


#pragma mark Greater Than Or Equal

#{compare_greater_than_equal_defs}


#pragma mark Masked Greater Than Or Equal

#{mask_compare_greater_than_equal_defs}


#pragma mark - Maths
#pragma mark Add

#{add_defs}


#pragma mark Subtract

#{sub_defs}


#pragma mark Multiply

#{mul_defs}


#pragma mark Multiply and Add

#{madd_defs}


#pragma mark Negated Multiply and Add

#{neg_madd_defs}


#pragma mark Multiply and Sub

#{msub_defs}


#pragma mark Negated Multiply and Sub

#{neg_msub_defs}


#pragma mark Divide

#{div_defs}


#pragma mark Modulo

#{mod_defs}


#pragma mark Rounding

#{round_nearest_away_defs}

#{round_nearest_even_defs}

#{round_zero_defs}

#{floor_defs}

#{ceil_defs}


#pragma mark Horizontal Add

#{hadd_defs}


#pragma mark Horizontal Subtract

#{hsub_defs}


#pragma mark Dot Product

#{dot_defs}


#pragma mark Sum

#{sum_defs}


#pragma mark Negate

#{neg_defs}


#pragma mark Absolute

#{abs_defs}


#pragma mark Min

#{min_defs}


#pragma mark Max

#{max_defs}


#pragma mark Clamp

#{clamp_defs}


#pragma mark Square Root

#{sqrt_defs}

#{inv_sqrt_defs}


#pragma mark Cube Root

#{cbrt_defs}

#{inv_cbrt_defs}


#pragma mark Power

#{pow_defs}


#pragma mark 2 Power

#{pow_2_defs}


#pragma mark Exponent

#{exp_defs}

#{exp_2_defs}


#pragma mark Logarithm

#{log_defs}

#{log_2_defs}


#pragma mark Sine

#{sin_defs}

#{pos_sin_defs}

#{pi_rad_sin_defs}

#{pos_pi_rad_sin_defs}

#{arc_sin_defs}


#pragma mark Cosine

#{half_pi_rad_cos_defs}

#{cos_defs}

#{arc_cos_defs}


#pragma mark Tangent

#{tan_defs}

#{qtr_pi_arc_tan_defs}

#{arc_tan_defs}

#{arc_tan_2_defs}


#pragma mark Cosecant

#{csc_defs}


#pragma mark Secant

#{sec_defs}


#pragma mark Cotangent

#{cot_defs}


#pragma mark - Reordering
#pragma mark Swizzle

#{swizzle_defs}


#pragma mark Interleave

#{interleave_defs}


#pragma mark Merge

#{merge_defs}


#pragma mark -

#undef CC_SIMD_MISSING_CCSimdZero
#undef CC_SIMD_MISSING_CCSimdSetSequence
#undef CC_SIMD_MISSING_CCSimdAndNot
#undef CC_SIMD_MISSING_CCSimdRotateLeft
#undef CC_SIMD_MISSING_CCSimdRotateLeftN
#undef CC_SIMD_MISSING_CCSimdRotateRight
#undef CC_SIMD_MISSING_CCSimdRotateRightN
#undef CC_SIMD_MISSING_CCSimdLowestUnset
#undef CC_SIMD_MISSING_CCSimdLowestSet
#undef CC_SIMD_MISSING_CCSimdHighestSet
#undef CC_SIMD_MISSING_CCSimdNextPow2
#undef CC_SIMD_MISSING_CCSimdMask
#undef CC_SIMD_MISSING_CCSimdMaskLowerPow2
#undef CC_SIMD_MISSING_CCSimdMaskHighestUnset
#undef CC_SIMD_MISSING_CCSimdCountLowestUnset
#undef CC_SIMD_MISSING_CCSimdCountSet
#undef CC_SIMD_MISSING_CCSimdCompareEqual
#undef CC_SIMD_MISSING_CCSimdCompareNotEqual
#undef CC_SIMD_MISSING_CCSimdCompareLessThan
#undef CC_SIMD_MISSING_CCSimdCompareLessThanEqual
#undef CC_SIMD_MISSING_CCSimdCompareGreaterThan
#undef CC_SIMD_MISSING_CCSimdCompareGreaterThanEqual
#undef CC_SIMD_MISSING_CCSimdMaskCompareNotEqual
#undef CC_SIMD_MISSING_CCSimdMadd
#undef CC_SIMD_MISSING_CCSimdNegMadd
#undef CC_SIMD_MISSING_CCSimdMsub
#undef CC_SIMD_MISSING_CCSimdNegMsub
#undef CC_SIMD_MISSING_CCSimdDiv
#undef CC_SIMD_MISSING_CCSimdMod
#undef CC_SIMD_MISSING_CCSimdHadd
#undef CC_SIMD_MISSING_CCSimdHsub
#undef CC_SIMD_MISSING_CCSimdDot
#undef CC_SIMD_MISSING_CCSimdClamp

#undef CC_SIMD_MISSING_CCSimdPosPiRadSin
#undef CC_SIMD_MISSING_CCSimdHalfPiRadCos
#undef CC_SIMD_MISSING_CCSimdPosSin
#undef CC_SIMD_MISSING_CCSimdPiRadSin
#undef CC_SIMD_MISSING_CCSimdSin
#undef CC_SIMD_MISSING_CCSimdArcSin
#undef CC_SIMD_MISSING_CCSimdCos
#undef CC_SIMD_MISSING_CCSimdArcCos
#undef CC_SIMD_MISSING_CCSimdTan
#undef CC_SIMD_MISSING_CCSimdQtrPiArcTan
#undef CC_SIMD_MISSING_CCSimdArcTan
#undef CC_SIMD_MISSING_CCSimdArcTan2
#undef CC_SIMD_MISSING_CCSimdCsc
#undef CC_SIMD_MISSING_CCSimdSec
#undef CC_SIMD_MISSING_CCSimdCot
#undef CC_SIMD_MISSING_CCSimdLog2
#undef CC_SIMD_MISSING_CCSimdLog
#undef CC_SIMD_MISSING_CCSimdPow
#undef CC_SIMD_MISSING_CCSimdPow2
#undef CC_SIMD_MISSING_CCSimdExp
#undef CC_SIMD_MISSING_CCSimdExp2
#undef CC_SIMD_MISSING_CCSimdCbrt
#undef CC_SIMD_MISSING_CCSimdInvCbrt

#define CC_SIMD_MISSING_CCSimdZero CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdSetSequence CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdAndNot CC_SIMD_#{width}_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdRotateLeft CC_SIMD_#{width}_UNSIGNED_TYPES
#define CC_SIMD_MISSING_CCSimdRotateLeftN CC_SIMD_#{width}_UNSIGNED_TYPES
#define CC_SIMD_MISSING_CCSimdRotateRight CC_SIMD_#{width}_UNSIGNED_TYPES
#define CC_SIMD_MISSING_CCSimdRotateRightN CC_SIMD_#{width}_UNSIGNED_TYPES
#define CC_SIMD_MISSING_CCSimdLowestUnset CC_SIMD_#{width}_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdLowestSet CC_SIMD_#{width}_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdHighestSet CC_SIMD_#{width}_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdNextPow2 CC_SIMD_#{width}_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdMask CC_SIMD_#{width}_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdMaskLowerPow2 CC_SIMD_#{width}_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdMaskHighestUnset CC_SIMD_#{width}_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdCountLowestUnset CC_SIMD_#{width}_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdCountSet CC_SIMD_#{width}_INTEGER_TYPES
#define CC_SIMD_MISSING_CCSimdCompareEqual CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdCompareNotEqual CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdCompareLessThan CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdCompareLessThanEqual CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdCompareGreaterThan CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdCompareGreaterThanEqual CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdMaskCompareNotEqual CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdMadd CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdNegMadd CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdMsub CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdNegMsub CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdDiv CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdMod CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdHadd CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdHsub CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdDot CC_SIMD_#{width}_TYPES
#define CC_SIMD_MISSING_CCSimdClamp CC_SIMD_#{width}_TYPES

#define CC_SIMD_MISSING_CCSimdPosPiRadSin CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdHalfPiRadCos CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdPosSin CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdPiRadSin CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdSin CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdArcSin CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdCos CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdArcCos CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdTan CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdQtrPiArcTan CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdArcTan CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdArcTan2 CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdCsc CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdSec CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdCot CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdLog2 CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdLog CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdPow CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdPow2 CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdExp CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdExp2 CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdCbrt CC_SIMD_#{width}_FLOAT_TYPES
#define CC_SIMD_MISSING_CCSimdInvCbrt CC_SIMD_#{width}_FLOAT_TYPES

#{element_types[0].sort.map { |args| args[1] }.join("\n\n")}

#{element_types[1].sort.map { |args| args[1] }.join("\n\n")}

#define CC_SIMD_#{width}_SIGNED_TYPES \\
#{signed_types.join(", \\\n")}

#define CC_SIMD_#{width}_UNSIGNED_TYPES \\
#{unsigned_types.join(", \\\n")}

#{mixed_element_types.sort.map { |args| args[1] }.join("\n\n")}

#define CC_SIMD_#{width}_TYPES \\
#{all_types.join(", \\\n")}

#define CC_SIMD_#{width}_INTEGER_TYPES \\
#{all_integer_types.join(", \\\n")}

#{all_integer_bit_types.join("\n\n")}

#define CC_SIMD_#{width}_FLOAT_TYPES \\
#{all_float_types.join(", \\\n")}

#if CC_HARDWARE_VECTOR_SUPPORT_ARM_NEON
#include <CommonC/Simd#{width}_arm.h>
#endif

#pragma mark - Fallback Implementations

#define CC_SIMD_WIDTH #{width}
#include <CommonC/SimdFallback.h>
#undef CC_SIMD_WIDTH

#endif
"""