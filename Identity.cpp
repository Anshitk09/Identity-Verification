#include <iostream>
#include <unordered_map>
#include <stdexcept>

class UserIdentity {
public:
    std::string name;
    std::string email;
    bool isVerified;
    std::string verifier;

    UserIdentity(const std::string& name, const std::string& email)
        : name(name), email(email), isVerified(false), verifier("") {}
};

class IdentityManager {
private:
    std::unordered_map<std::string, UserIdentity> identities;

public:
    void registerIdentity(const std::string& userId, const std::string& name, const std::string& email) {
        if (identities.find(userId) != identities.end()) {
            throw std::invalid_argument("Identity already registered");
        }
        identities[userId] = UserIdentity(name, email);
        std::cout << "Identity registered: " << userId << std::endl;
    }

    void verifyIdentity(const std::string& userId, const std::string& verifierId) {
        auto it = identities.find(userId);
        if (it == identities.end()) {
            throw std::invalid_argument("Identity not registered");
        }
        if (it->second.isVerified) {
            throw std::invalid_argument("Identity already verified");
        }
        it->second.isVerified = true;
        it->second.verifier = verifierId;
        std::cout << "Identity verified: " << userId << " by " << verifierId << std::endl;
    }

    UserIdentity getIdentity(const std::string& userId) {
        auto it = identities.find(userId);
        if (it == identities.end()) {
            throw std::invalid_argument("Identity not registered");
        }
        return it->second;
    }
};

int main() {
    IdentityManager manager;

    // Register identities
    manager.registerIdentity("user1", "Alice", "alice@example.com");
    manager.registerIdentity("user2", "Bob", "bob@example.com");

    // Verify identity
    manager.verifyIdentity("user1", "verifier1");

    // Retrieve identity
    UserIdentity identity1 = manager.getIdentity("user1");
    std::cout << "Retrieved Identity: Name: " << identity1.name 
              << ", Email: " << identity1.email 
              << ", Verified: " << identity1.isVerified 
              << ", Verifier: " << identity1.verifier << std::endl;

    UserIdentity identity2 = manager.getIdentity("user2");
    std::cout << "Retrieved Identity: Name: " << identity2.name 
              << ", Email: " << identity2.email 
              << ", Verified: " << identity2.isVerified 
              << ", Verifier: " << identity2.verifier << std::endl;

    return 0;
}
