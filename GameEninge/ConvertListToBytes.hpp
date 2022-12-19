#include <boost/algorithm/string/regex.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>

/**
 * @brief contains methods which can encode an vector to bytes which can be send over the internet
*/
namespace spic::internal::networking
{
    /**
     * @brief Encodes an map to an string
     * @tparam K Random value/object
     * @tparam V Random value/object
     * @param data The map
     * @return 
    */
    template<class K, class V>
    std::string encode_map(std::map<K, V> data) {
        std::string buffer;
        boost::iostreams::back_insert_device<std::string> inserter(buffer);
        boost::iostreams::stream<boost::iostreams::back_insert_device<std::string>> ostr(inserter);
        boost::archive::binary_oarchive oa(ostr);
        oa << data;
        ostr.flush();
        return buffer;
    }

    /**
     * @brief Decodes an map to an string
     * @tparam K Random value/object
     * @tparam V Random value/object
     * @param bytes The string
     * @return
    */
    template<class K, class V>
    std::map<K, V> decode_map(std::string bytes) {
        std::map<K, V> map;
        boost::iostreams::basic_array_source<char> device(bytes.data(), bytes.size());
        boost::iostreams::stream<boost::iostreams::basic_array_source<char>> istr(device);
        boost::archive::binary_iarchive ia(istr);
        ia >> map;
        return map;
    }
}