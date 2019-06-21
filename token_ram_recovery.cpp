#include <eosio/asset.hpp>
#include <eosio/eosio.hpp>

#include <string>

using namespace eosio;
using std::string;

class[[eosio::contract]] token : public contract
{
private:
    struct [[eosio::table]] account
    {
        asset balance;

        uint64_t primary_key() const { return balance.symbol.code().raw(); }
    };

    struct [[eosio::table]] currency_stats
    {
        asset supply;
        asset max_supply;
        name issuer;

        uint64_t primary_key() const { return supply.symbol.code().raw(); }
    };

    typedef eosio::multi_index<name("accounts"), account> accounts;
    typedef eosio::multi_index<name("stat"), currency_stats> stats;

public:
    using contract::contract;

    [[eosio::action]] void destroytoken(string symbol) {
        require_auth(_self);

        symbol_code sym(symbol);
        stats stats_table(_self, sym.raw());
        auto existing = stats_table.find(sym.raw());
        check(existing != stats_table.end(), "Token with symbol does not exist");

        stats_table.erase(existing);
    };

    [[eosio::action]] void destroyacc(string symbol, name account) {
        require_auth(_self);

        symbol_code sym(symbol);
        accounts accounts_table(_self, account.value);
        const auto &row = accounts_table.get(sym.raw(), "No balance object found for provided account and symbol");
        accounts_table.erase(row);
    };
};

EOSIO_DISPATCH(token, (destroytoken)(destroyacc))
