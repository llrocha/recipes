#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <set>
#include <exception>
#include <iostream>
namespace pt = boost::property_tree;

struct load_config
{
    std::string m_file;               // filename
    int m_size;                       // size
    void load(const std::string &filename);
    void save(const std::string &filename);
};


void load_config::load(const std::string &filename)
{
    pt::ptree tree;

    pt::read_xml(filename, tree);

    m_file = tree.get<std::string>("config.filename");

    m_size = tree.get("config.size", 0);

}

//[load_config_save
void load_config::save(const std::string &filename)
{
    // Create an empty property tree object.
    pt::ptree tree;

    // Put the simple values into the tree. The integer is automatically
    // converted to a string. Note that the "debug" node is automatically
    // created if it doesn't exist.
    tree.put("config.filename", m_file);
    tree.put("config.size", m_size);

    pt::write_xml(filename, tree);
}
//]

int main()
{
    try
    {
        load_config ds;
        ds.load("config.xml");
        ds.save("load_config_out.xml");
        std::cout << "Success\n";
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << "\n";
    }
    return 0;
}
