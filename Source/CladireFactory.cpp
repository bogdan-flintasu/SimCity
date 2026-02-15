#include "../Headers/CladireFactory.h"
#include "../Headers/CladireBuilder.h"
#include "../Headers/Strada.h"
#include "../Headers/Casa.h"
#include "../Headers/Bloc.h"

std::unique_ptr<Strada> CladireFactory::creeaza_strada(const std::vector<std::string>& inputs, double lungime) {
    return std::make_unique<Strada>(0, inputs[0], std::stod(inputs[1]), 100, (inputs[3] == "1"), (inputs[4] == "1"), std::stoi(inputs[2]), lungime);
}

std::unique_ptr<CladireRezidentiala> CladireFactory::creeaza_rezidentiala(const ui::ToolType tip, const std::vector<std::string>& inputs) {
    if (tip == ui::ToolType::CASA)
        return std::make_unique<Casa>(0, inputs[0], std::stod(inputs[1]), std::stod(inputs[2]), std::stoi(inputs[3]), std::stoi(inputs[4]));

    if (tip == ui::ToolType::BLOC)
        return std::make_unique<Bloc>(0, inputs[0], std::stod(inputs[1]), std::stod(inputs[2]), std::stoi(inputs[3]), std::stoi(inputs[4]));

    return nullptr;
}

std::unique_ptr<CladirePublica> CladireFactory::creeaza_publica(const ui::ToolType tip, const std::vector<std::string>& inputs) {
    CladireBuilder builder;
    builder.setNume(inputs[0]).setCost(std::stod(inputs[1]));

    switch (tip) {
        case ui::ToolType::FABRICA:
            return builder.setSuprafata(std::stod(inputs[2]))
                          .setCapacitate(std::stoi(inputs[4]))
                          .setPoluare(50.0)
                          .setInchiriat(inputs[9] == "1")
                          .buildFabrica();

        case ui::ToolType::SPATIU_VERDE:
            return builder.setSuprafata(std::stod(inputs[3]))
                          .setMentenanta(std::stod(inputs[4]))
                          .setInchiriat(inputs[6] == "1")
                          .buildSpatiuVerde();

        case ui::ToolType::SPATIU_COMERCIAL:
            return builder.setCapacitate(std::stoi(inputs[3]))
                          .setInchiriat(inputs[9] == "1")
                          .buildComercial();

        case ui::ToolType::CLADIRE_ADMINISTRATIVA:
            return builder.setCapacitate(std::stoi(inputs[3]))
                          .setInchiriat(inputs[7] == "1")
                          .buildAdmin();

        case ui::ToolType::CLADIRE_SERVICII:
            return builder.setCapacitate(std::stoi(inputs[3]))
                          .setInchiriat(inputs[6] == "1")
                          .buildServicii();

        case ui::ToolType::CLADIRE_EDUCATIE:
            return builder.setCapacitate(std::stoi(inputs[3]))
                          .setRating(9.5)
                          .setInchiriat(inputs[10] == "1")
                          .buildScoala();

        default: return nullptr;
    }
}