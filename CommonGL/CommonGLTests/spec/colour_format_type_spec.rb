def colour_format_channel_type(channel, bits, offset)
    "((#{channel}|(#{bits}<<CCColourFormatChannelBitSize))<<CCColourFormatChannelOffset#{offset})"
end

def get_colour_format_channel_type(channel_representation, channel, bits, offset)
    channel_representation[Regexp.new(Regexp.quote(colour_format_channel_type(channel, bits, offset)))]
end

RSpec.describe 'Colour format' do
    shared_examples 'channel representation' do |representation, channel, bits, offset|
        rep = get_colour_format_channel_type(representation, channel, bits, offset)
        it "\"#{colour_format_channel_type(channel, bits, offset)}\"" do
            expect(rep).to_not be_nil
        end
    end

    shared_examples 'format type' do |representation, type|
        it "\"#{type}\"" do
            expect(representation[Regexp.new(Regexp.quote(type))]).to_not be_nil
        end
    end

    src = File.read('../CommonGL/ColourFormat.h')

    context 'RGB type' do
        rgb_colour_formats = src[/(?<=typedef NS_OPTIONS\(uint64_t, CCColourFormatRGB\) {).*?(?=})/m].gsub(/(\/\/.*)/, '').gsub(/\s/, '').split(',')
        rgb_colour_formats.each { |format|
            name = format[/(?<=CCColourFormat).*?(?==)/]
            representation = format[/(?<==).*/]

            index = 0
            context name do
                type = name[/(?<=\d)\D+/]
                case type
                when 'Unorm'
                    it_should_behave_like 'format type', representation, 'CCColourFormatTypeUnsignedInteger|CCColourFormatNormalized'
                when 'Snorm'
                    it_should_behave_like 'format type', representation, 'CCColourFormatTypeSignedInteger|CCColourFormatNormalized'
                when 'Uint'
                    it_should_behave_like 'format type', representation, 'CCColourFormatTypeUnsignedInteger'
                when 'Sint'
                    it_should_behave_like 'format type', representation, 'CCColourFormatTypeSignedInteger'
                when 'Float'
                    it_should_behave_like 'format type', representation, 'CCColourFormatTypeFloat'
                end

                name.scan(/\D+\d+/).each { |channel_size|
                    bits = channel_size[/\d+/]
                    channel_size.scan(/\D/).each { |channel|
                        describe "channel #{channel}" do
                            case channel
                            when 'R'
                                it_should_behave_like 'channel representation', representation, 'CCColourFormatChannelRed', bits, index
                            when 'G'
                                it_should_behave_like 'channel representation', representation, 'CCColourFormatChannelGreen', bits, index
                            when 'B'
                                it_should_behave_like 'channel representation', representation, 'CCColourFormatChannelBlue', bits, index
                            when 'A'
                                it_should_behave_like 'channel representation', representation, 'CCColourFormatChannelAlpha', bits, index
                            end
                        end

                        index += 1
                    }
                }
            end
        }
    end
end
