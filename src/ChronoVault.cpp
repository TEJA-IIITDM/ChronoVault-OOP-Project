#include "ChronoVault.h"
#include <stdexcept>
#include <utility>

Mission::Mission(int id, std::string name, std::string timeline, std::string explorerType, int energy)
    : id_(id), name_(std::move(name)), timeline_(std::move(timeline)), explorerType_(std::move(explorerType)), status_("Planned"), result_("Awaiting launch"), energy_(energy) {}
void Mission::launch(const Explorer& explorer) {
    status_ = "Completed";
    result_ = explorer.action();
}
ChronoVault::ChronoVault() {
    explorers_.push_back(std::make_unique<Historian>("Ada"));
    explorers_.push_back(std::make_unique<Engineer>("Nikola"));
    explorers_.push_back(std::make_unique<Guardian>("Mira"));
}
ChronoVault::~ChronoVault() = default;
Mission& ChronoVault::createMission(const std::string& name, const std::string& timeline, const std::string& type, int energy) {
    if (name.empty() || timeline.empty()) throw std::invalid_argument("Enter a mission name and choose a timeline.");
    if (energy < 20 || energy > 200) throw std::invalid_argument("Energy must be between 20 and 200 CU.");
    if (energy > energy_) throw std::invalid_argument("Not enough energy available for this mission.");
    bool valid = false;
    for (const auto& e : explorers_) if (e->type() == type) valid = true;
    if (!valid) throw std::invalid_argument("Choose a valid explorer type.");
    energy_ -= energy;
    missions_.emplace_back(nextId_++, name, timeline, type, energy);
    return missions_.back();
}
void ChronoVault::launchMission(int id) {
    for (auto& m : missions_) {
        if (m.id() == id) {
            if (m.status() != "Planned") throw std::invalid_argument("This mission has already been launched.");
            for (const auto& e : explorers_) if (e->type() == m.explorerType()) { m.launch(*e); return; }
        }
    }
    throw std::invalid_argument("Mission not found.");
}
