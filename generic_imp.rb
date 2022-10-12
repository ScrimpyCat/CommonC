param_count = 1
max_imps = 20
max_types = 10
include_header = true
params = []
symbols = []
templates = []
namespace = 'EXAMPLE'
template_header = '<ExampleTemplate.h>'
defaults = []
mappings = []

class String
    def format
        self.downcase
    end
end

input = nil
ARGV.each { |e|
    if input != nil and (not [:default, :mapping].include?(input) or not e.start_with? '-')
        case input
        when :param_count
            param_count = e.to_i
        when :max_imps
            max_imps = e.to_i
        when :max_types
            max_types = e.to_i
        when :param
            params << e
        when :namespace
            namespace = e
        when :template_header
            template_header = e
        when :template
            src = File::read(e)
            symbols = src.scan(/^[^\/\n]*?\#define .*?_T\(.*?\).*?CC_TEMPLATE_REF\(.*\)/)
            templates = src.scan(/CC_TEMPLATE\(.*\)/).uniq!
        when :default
            defaults.last << e
        when :mapping
            mappings << e
        end

        input = nil if not [:default, :mapping].include?(input)
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
        when '--namespace'
            input = :namespace
        when '-n'
            input = :namespace
        when '--template-header'
            input = :template_header
        when '-th'
            input = :template_header
        when '--template'
            input = :template
        when '-t'
            input = :template
        when '--default'
            input = :default
            defaults << []
        when '-d'
            input = :default
            defaults << []
        when '--map'
            input = :mapping
        when '-m'
            input = :mapping
        when '--lowercase'
            class String
                def format
                    self.downcase
                end
            end
        when '--uppercase'
            class String
                def format
                    self.upcase
                end
            end
        end 
    end
}

class NilClass
    def decl
        nil
    end

    def type_list
        nil
    end
end

class String
    def decl
        "CC_TYPE_DECL(#{self})"
    end

    def formatter
        # todo: handle more complex types such as FPTYPE
        ptrs = self.scan(/PTYPE\(/).map { '*' }.join('')
        if ptrs.length > 0
            return lambda{ |x| "CC_MAP_WITH(CC_GENERIC_FORMAT, #{ptrs}, #{x})" }
        else
            return lambda{ |x| x }
        end
    end
end

String.class_eval do
    define_method(:type_list) do
        "CC_GENERIC_NAMED_TYPE_LIST(#{self}, #{namespace}_COUNT)"
    end
end

if params.count == 0
    if param_count == 1
        params = [:T] 
    else
        params = [:Tx, :Ty, :Tz, :Tw]
    end
end

params = params[0, param_count]

mappings.each { |m|
    mapping = m.split('=')
    if mapping.count > 1
        puts "#ifndef #{mapping.first}"
        puts "#define #{mapping.first} #{mapping.last}"
        puts "#endif"
        puts ""
    end
}

if include_header
    puts "#include <CommonC/Generics.h>"
    puts ""
end

sym_calls = []
sym_refs = []

symbols.each { |s|
    macro = s[/\w*(?=\()/]
    args = s[/\(.*?\)/][1..-2].split(',').map { |a| a.strip }
    template = s[/(?<=CC_TEMPLATE_REF\()\w*/]
    t_def = templates.find { |t| t[/\W#{template}\W/] }
    t_params = t_def.scan(/(?<=[\W\(])(#{params.join('|')})(?=[\W\)])/).flatten
    t_types = s[/(?<=CC_TEMPLATE_REF\().*/].chop.split(',').drop(1).map { |t| t.strip }

    if t_def[/\W#{template}\W*?[,\(\)]/][-1] != ')'
        t_arg_names = t_def[/(?<=\W#{template})\W*.*/].chop[/(?<=\().*(?=\))/].scan(/(\w+(?=,)|\w+$)/).flatten
        gen_args = []
        formatters = []

        args.each { |a|
            i = t_types.drop(1).index { |t| t == a or t[/\W#{a}\W/] != nil }
            if i != nil
                gen_args << t_arg_names[i]
                formatters << t_types[i + 1].formatter
            end
        }

        default_refs = defaults.map.with_index { |d, r|
            defs = Hash[d.map { |p| p.split('=') }]
            "CC_RECURSIVE_#{r}_GENERIC((#{gen_args.map.with_index { |a, i| "((typeof(#{defs[params[i].to_s].decl || a.format})){0})" }.join(', ')}), #{macro}, CC_TYPE_DECL, CC_GENERIC_ERROR, #{t_params.uniq.map.with_index { |p, i| "(#{formatters[i].call("#{defs[p].type_list || "#{namespace}_#{p}"}")})" }.join(', ')})"
        }

        ref = "#define #{template}_Ref(#{t_arg_names.map(&:format).join(', ')}) CC_GENERIC((#{gen_args.map { |a| "((typeof(#{a.format})){0})" }.join(', ')}), #{macro}, CC_GENERIC_MATCH, CC_GENERIC_ERROR, #{t_params.uniq.map.with_index { |p, i| "(#{formatters[i].call("#{namespace}_#{p}")})" }.join(', ')})"
        default_refs.each { |d| ref.gsub!('CC_GENERIC_ERROR', d) }

        sym_calls << "#define #{template}(#{t_arg_names.map(&:format).join(', ')}) #{template}_Ref(#{t_arg_names.map(&:format).join(', ')})(#{t_arg_names.map(&:format).join(', ')})"
        sym_refs << ref
    else
        default_refs = defaults.map.with_index { |d, r|
            defs = Hash[d.map { |p| p.split('=') }]
            "CC_RECURSIVE_#{r}_GENERIC((((typeof(#{defs[t_params.uniq.first].decl || 't'.format})){0})), #{macro}, CC_TYPE_DECL, CC_GENERIC_ERROR, #{t_params.uniq.map { |p| "(#{defs[p].type_list || "#{namespace}_#{p}"})" }.join(', ')})"
        }

        ref = "#define #{template}_Ref(#{'t'.format}) CC_GENERIC((((typeof(#{'t'.format})){0})), #{macro}, CC_GENERIC_MATCH, CC_GENERIC_ERROR, #{t_params.uniq.map { |p| "(#{namespace}_#{p})" }.join(', ')})"
        default_refs.each { |d| ref.gsub!('CC_GENERIC_ERROR', d) }

        sym_refs << ref
    end
}

if sym_calls.count
    puts sym_calls
    puts ""
end

if sym_refs.count
    puts sym_refs
    puts ""
end

params.each { |p|
    puts "#define #{namespace}_#{p} CC_GENERIC_INDEXED_TYPE_LIST(#{namespace}_#{p}, #{namespace}_COUNT)"
}

puts ""

max_imps.times { |i|
    params.each { |p|
        puts "#ifndef CC_MANGLE_TYPE_#{namespace}_#{p}#{i}"
        puts "#define CC_MANGLE_TYPE_#{namespace}_#{p}#{i} #{namespace}_#{p}#{i}"
        puts "#endif"
        puts ""
    }
}

params.each { |p|
    max_imps.times { |i|
        max_types.times { |t|
            puts "#define CC_MANGLE_TYPE_#{t}_#{namespace}_#{p}#{i} CC_MANGLE_TYPE_#{namespace}_#{p}#{i}"
        }
    }
    puts ""
}

params.each { |p|
    max_imps.times { |i| 
        puts "#define CC_TYPE_DECL_#{namespace}_#{p}#{i}(...) #{namespace}_#{p}#{i}, __VA_ARGS__" 
    }
    max_imps.times { |i|
        max_types.times { |t|
            puts "#define CC_TYPE_DECL_#{t}_#{namespace}_#{p}#{i} CC_TYPE_DECL_#{namespace}_#{p}#{i},"
        }
    }
    puts ""
}

puts "#ifdef #{namespace}_COUNT"
puts "#define CC_GENERIC_COUNT #{namespace}_COUNT"
puts "#endif"
puts ""
puts "#ifndef CC_GENERIC_TEMPLATE"
puts "#define CC_GENERIC_TEMPLATE #{template_header}"
puts "#endif"
puts ""
puts "#undef CC_GENERIC_TYPE"
puts "#define CC_GENERIC_TYPE #{namespace}"
puts "#include <CommonC/Generic#{param_count}.h>"
puts ""

max_imps.times { |i|
    puts "#if CC_GENERIC_COUNT < #{i + 1}"
    params.each { |p|
        puts "#undef CC_MANGLE_TYPE_#{namespace}_#{p}#{i}"
    }
    puts "#endif"
    puts ""
}

puts "#undef #{namespace}_COUNT"
puts ""

max_imps.times { |i|
    if i == 0
        puts "#if CC_GENERIC_COUNT == #{i + 1}"
    else
        puts "#elif CC_GENERIC_COUNT == #{i + 1}"
    end

    puts "#define #{namespace}_COUNT #{i + 1}"
}

puts "#else"
puts "#error Add additional cases"
puts "#endif"
puts ""
puts "#undef CC_GENERIC_COUNT"

params.each { |p|
    puts ""
    max_imps.times { |i| 
        puts "#define CC_TYPE_#{namespace}_#{p}#{i}(...) #{namespace}_#{p}#{i}" 
    }
    max_imps.times { |i|
        max_types.times { |t|
            puts "#define CC_TYPE_#{t}_#{namespace}_#{p}#{i} CC_TYPE_#{namespace}_#{p}#{i},"
        }
    }
}

mappings = mappings.map { |m| m.split('=').first }.select { |m| not m[/^(#{params.join('|')})$/] }
if mappings.count > 0
    puts ""
    puts "#ifndef CC_GENERIC_PRESERVE_TYPE"
    mappings.each { |m| puts "#undef #{m}" }
    puts "#endif"
end
