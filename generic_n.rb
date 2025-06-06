param_count = 1
max_imps = 20
max_types = 10
include_header = true
params = []

input = nil
ARGV.each { |e|
    if input != nil
        case input
        when :param_count
            param_count = e.to_i
        when :max_imps
            max_imps = e.to_i
        when :max_types
            max_types = e.to_i
        when :param
            params << e
        end

        input = nil
    elsif e.start_with? '-'
        case e
        when '--param-count'
            input = :param_count
        when '-pc'
            input = :param_count
        when '--max-imps'
            input = :max_imps
        when '-mi'
            input = :max_imps
        when '--max-types'
            input = :max_types
        when '-mt'
            input = :max_types
        when '--include_header'
            include_header = true
        when '-ih'
            include_header = true
        when '--exclude_header'
            include_header = false
        when '-eh'
            include_header = false
        when '--param'
            input = :param
        when '-p'
            input = :param
        end
    end
}

if params.count == 0
    if param_count == 1
        params = [:T]
    else
        params = [:Tx, :Ty, :Tz, :Tw]
    end
end

params = params[0, param_count]

if include_header
    puts "#include <CommonC/Template.h>"
    puts ""
end

params.each { |p|
    max_imps.times { |i|
        puts "#define CC_TYPE_CC_GENERIC_#{p}#{i}(...) CC_GENERIC_#{p}(#{i})"
    }
    max_imps.times { |i|
        max_types.times { |t|
            puts "#define CC_TYPE_#{t}_CC_GENERIC_#{p}#{i} CC_TYPE_CC_GENERIC_#{p}#{i},"
        }
    }
    puts ""
}

params.each { |p|
    max_imps.times { |i|
        puts "#define CC_PRESERVE_CC_TYPE_CC_GENERIC_#{p}#{i} CC_TYPE_CC_GENERIC_#{p}#{i}"
    }
    puts ""
}

params.each { |p|
    max_imps.times { |i|
        puts "#define CC_TYPE_DECL_CC_GENERIC_#{p}#{i}(...) CC_GENERIC_#{p}(#{i}), __VA_ARGS__"
    }
    max_imps.times { |i|
        max_types.times { |t|
            puts "#define CC_TYPE_DECL_#{t}_CC_GENERIC_#{p}#{i} CC_TYPE_DECL_CC_GENERIC_#{p}#{i},"
        }
    }
    puts ""
}

params.each { |p|
    puts "#define CC_GENERIC_#{p}(n) CC_GENERIC_#{p}_(CC_GENERIC_TYPE, n)"
    puts "#define CC_GENERIC_#{p}_(t, n) CC_GENERIC_#{p}__(t, n)"
    puts "#define CC_GENERIC_#{p}__(t, n) t##_#{p}##n"
    puts ""
}

max_imps.times { |i|
    if i == 0
        puts "#if !defined(CC_GENERIC_COUNT) || CC_GENERIC_COUNT == #{i}"
    else
        puts "#elif CC_GENERIC_COUNT == #{i}"
    end

    params.each { |p|
        puts "typedef CC_TYPE_DECL(#{p}) CC_GENERIC_#{p}(#{i});"
    }
    params.each { |p|
        puts "#undef #{p}"
    }
    params.each { |p|
        puts "#define #{p} CC_GENERIC_#{p}#{i}"
    }

    puts ""
    puts "#undef CC_GENERIC_COUNT"
    puts "#define CC_GENERIC_COUNT #{i + 1}"
    puts ""
}

puts "#else"
puts "#error Add additional cases"
puts "#endif"
puts ""
puts "#include CC_GENERIC_TEMPLATE"
puts ""
puts "#ifndef CC_GENERIC_PRESERVE_TYPE"
params.each { |p|
    puts "#undef #{p}"
}
puts "#endif"
puts ""
puts "#ifndef CC_GENERIC_PRESERVE_HEADER"
puts "#undef CC_GENERIC_TEMPLATE"
puts "#endif"
