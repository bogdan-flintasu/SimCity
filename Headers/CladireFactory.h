#ifndef OOP_CLADIREFACTORY_H
#define OOP_CLADIREFACTORY_H

#include <memory>
#include <vector>
#include <string>
#include "../UI/SideMenu.h"

class Strada;
class CladireRezidentiala;
class CladirePublica;

class CladireFactory {
public:

    static std::unique_ptr<Strada> creeaza_strada(const std::vector<std::string>& inputs, double lungime);
    static std::unique_ptr<CladireRezidentiala> creeaza_rezidentiala(ui::ToolType tip, const std::vector<std::string>& inputs);
    static std::unique_ptr<CladirePublica> creeaza_publica(ui::ToolType tip, const std::vector<std::string>& inputs);
};

#endif