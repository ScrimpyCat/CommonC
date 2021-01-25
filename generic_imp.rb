param_count = 1
max_imps = 20
max_types = 10
include_header = true
params = []
symbols = []
templates = []
namespace = 'EXAMPLE'
template_header = '<ExampleTemplate.h>'

class String
    def format
        self.downcase
    end
end

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
        when :namespace
            namespace = e
        when :template_header
            template_header = e
        when :template
            src = File::read(e)
            symbols = src.scan(/^[^\/\n]*?\#define .*?_T\(.*?\).*?CC_TEMPLATE_REF\(.*\)/)
            templates = src.scan(/CC_TEMPLATE\(.*\)/).uniq!
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

if params.count == 0
    if param_count == 1
        params = [:T] 
    else
        params = [:Tx, :Ty, :Tz, :Tw]
    end
end

params = params[0, param_count]

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

        args.each { |a|
            i = t_types.drop(1).index { |t| t == a or t[/\W#{a}\W/] != nil }
            if i != nil
                gen_args << t_arg_names[i]
            end
        }

        sym_calls << "#define #{template}(#{t_arg_names.map(&:format).join(', ')}) #{template}_Ref(#{t_arg_names.map(&:format).join(', ')})(#{t_arg_names.map(&:format).join(', ')})"
        sym_refs << "#define #{template}_Ref(#{t_arg_names.map(&:format).join(', ')}) CC_GENERIC((#{gen_args.map { |a| "((typeof(#{a.format})){0})" }.join(', ')}), #{macro}, CC_GENERIC_MATCH, #{t_params.uniq.map { |p| "(#{namespace}_#{p})" }.join(', ')})"
    else
        sym_refs << "#define #{template}_Ref(#{'t'.format}) CC_GENERIC((((typeof(#{'t'.format})){0})), #{macro}, CC_GENERIC_MATCH, #{t_params.uniq.map { |p| "(#{namespace}_#{p})" }.join(', ')})"
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

puts "#ifdef #{namespace}_COUNT"
puts "#define CC_GENERIC_COUNT #{namespace}_COUNT"
puts "#endif"
puts ""
puts "#undef CC_GENERIC_TYPE"
puts "#undef CC_GENERIC_TEMPLATE"
puts "#define CC_GENERIC_TYPE #{namespace}"
puts "#define CC_GENERIC_TEMPLATE #{template_header}"
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