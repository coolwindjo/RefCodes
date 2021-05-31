#include <iostream>
#include <string>

class People
{
private:
    std::string name;
public:
    People(std::string s)
        : name(s)
    {}
    People(const People &p)
        : name(p.name)
    {
        std::cout << "copy" <<std::endl;
    }
    People(People &&p) noexcept
        : name(std::move(p.name))
    {
        std::cout << "move" <<std::endl;
    }

    People& operator=(const People &p)
    {
        name = p.name;
        std::cout << "copy=" <<std::endl;
        return *this;
    }

    People& operator=(const People &&p) noexcept
    {
        name = std::move(p.name);
        std::cout << "move=" <<std::endl;
        return *this;
    }
};
