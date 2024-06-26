enum clothing
{ 
    none,
    shirt, 
    legs, 
    feet, 
    face, 
    hand, 
    back, 
    head, 
    charms,
    ances
};

#include <unordered_map>

class item {
    public:
    unsigned short id{}; /* item identity */
    std::string raw_name{}; /* the exact name of the item including uppercases */
    std::string name{}; /* prefered for easy access; same as raw_name but all lowercased */
    short hits{};
    clothing cloth_type{clothing::none};
}; std::unordered_map<int, item> items;

std::vector<std::byte> im_data(60, std::byte{0x00});
signed hash{};

template<typename T>
void shift_pos(std::vector<std::byte>& data, int& pos, T& value) {
    for (size_t i = 0; i < sizeof(T); ++i) 
        reinterpret_cast<std::byte*>(&value)[i] = data[pos + i];
    pos += sizeof(T);
}

bool cache_items() {
    short version{0};
    int pos{60}, count{0};
    shift_pos(im_data, pos, version);
    shift_pos(im_data, pos, count);
    items.reserve(count);
    for (int i = 0; i < count; i++) {
        item im{};
        shift_pos(im_data, pos, im.id); pos += sizeof(unsigned short);
        pos += sizeof(int);
        {
            short len = *(reinterpret_cast<short*>(&im_data[pos]));
            pos += sizeof(short);
            for (short i = 0; i < std::move(len); i++)
                im.raw_name += static_cast<char>(im_data[pos] ^ std::byte(std::string_view{"PBG892FXX982ABC*"}[(i + im.id) % std::string_view{"PBG892FXX982ABC*"}.length()])),
                ++pos;
        }
        im.name = im.raw_name;
        std::ranges::transform(im.name, im.name.begin(), [](char c) { return std::tolower(c); });
        {
            short len = *(reinterpret_cast<short*>(&im_data[pos]));
            pos += sizeof(short);
            for (short i = 0; i < std::move(len); i++)
                ++pos;
        }
        pos += 14;
        unsigned char raw_hits{};
        shift_pos(im_data, pos, raw_hits);
        im.hits = raw_hits;
        if (im.hits not_eq 0/*math in C++ cannot divide 0 values*/) im.hits /= 6; /* unknown reason behind why break hit is muliplied by 6 then having to divide by 6 */
        pos += sizeof(int);
        unsigned char cloth_type{};
        shift_pos(im_data, pos, cloth_type);
        im.cloth_type = static_cast<clothing>(cloth_type);
        pos += 3;
        {
            short len = *(reinterpret_cast<short*>(&im_data[pos]));
            pos += sizeof(short);
            for (short i = 0; i < std::move(len); i++)
                ++pos;
        }
        pos += 8;
        {
            short len = *(reinterpret_cast<short*>(&im_data[pos]));
            pos += sizeof(short);
            for (short i = 0; i < std::move(len); i++)
                ++pos;
        }
        {
            short len = *(reinterpret_cast<short*>(&im_data[pos]));
            pos += sizeof(short);
            for (short i = 0; i < std::move(len); i++)
                ++pos;
        }
        {
            short len = *(reinterpret_cast<short*>(&im_data[pos]));
            pos += sizeof(short);
            for (short i = 0; i < std::move(len); i++)
                ++pos;
        }
        {
            short len = *(reinterpret_cast<short*>(&im_data[pos]));
            pos += sizeof(short);
            for (short i = 0; i < std::move(len); i++)
                ++pos;
        }
        pos += 24;
        {
            short len = *(reinterpret_cast<short*>(&im_data[pos]));
            pos += sizeof(short);
            for (short i = 0; i < std::move(len); i++)
                ++pos;
        }
        {
            short len = *(reinterpret_cast<short*>(&im_data[pos]));
            pos += sizeof(short);
            for (short i = 0; i < std::move(len); i++)
                ++pos;
        }
        {
            short len = *(reinterpret_cast<short*>(&im_data[pos]));
            pos += sizeof(short);
            for (short i = 0; i < std::move(len); i++)
                ++pos;
        }
        pos += 80;
        {
            short len = *(reinterpret_cast<short*>(&im_data[pos]));
            pos += sizeof(short);
            for (short i = 0; i < std::move(len); i++)
                ++pos;
        }
        pos += 13;
        pos += 8;
        pos += 25;
        {
            short len = *(reinterpret_cast<short*>(&im_data[pos]));
            pos += sizeof(short);
            for (short i = 0; i < std::move(len); i++)
                ++pos;
        }
        {
            short len = *(reinterpret_cast<short*>(&im_data[pos]));
            pos += sizeof(short);
            for (short i = 0; i < std::move(len); i++)
                ++pos;
        }
        pos += 8;
        if (im.name.contains("ancestral") and not im.name.contains("seed"))
            im.cloth_type = clothing::ances;
        items.emplace(i, std::move(im));
    }
    return true;
}