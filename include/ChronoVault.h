#pragma once
#include <memory>
#include <string>
#include <vector>

class Explorer {
protected:
    std::string name_;
public:
    explicit Explorer(std::string name) : name_(std::move(name)) {}
    virtual ~Explorer() = default;
    std::string name() const { return name_; }
    virtual std::string type() const = 0;
    virtual std::string action() const = 0;
};
class Historian : public Explorer {
public: using Explorer::Explorer;
    std::string type() const override { return "Historian"; }
    std::string action() const override { return "Verified historical records"; }
};
class Engineer : public Explorer {
public: using Explorer::Explorer;
    std::string type() const override { return "Engineer"; }
    std::string action() const override { return "Repaired timeline equipment"; }
};
class Guardian : public Explorer {
public: using Explorer::Explorer;
    std::string type() const override { return "Guardian"; }
    std::string action() const override { return "Protected the timeline"; }
};

class Mission {
private:
    int id_;
    std::string name_, timeline_, explorerType_, status_, result_;
    int energy_;
public:
    Mission(int id, std::string name, std::string timeline, std::string explorerType, int energy);
    int id() const { return id_; }
    std::string name() const { return name_; }
    std::string timeline() const { return timeline_; }
    std::string explorerType() const { return explorerType_; }
    std::string status() const { return status_; }
    std::string result() const { return result_; }
    int energy() const { return energy_; }
    void launch(const Explorer& explorer);
    bool operator==(const Mission& other) const { return id_ == other.id_; }
};

class ChronoVault {
private:
    int energy_ = 500;
    int nextId_ = 1;
    std::vector<Mission> missions_;
    std::vector<std::unique_ptr<Explorer>> explorers_;
public:
    ChronoVault();
    ~ChronoVault();
    ChronoVault(const ChronoVault&) = delete;
    ChronoVault& operator=(const ChronoVault&) = delete;
    int energy() const { return energy_; }
    const std::vector<Mission>& missions() const { return missions_; }
    const std::vector<std::unique_ptr<Explorer>>& explorers() const { return explorers_; }
    Mission& createMission(const std::string& name, const std::string& timeline, const std::string& type, int energy);
    void launchMission(int id);
};
