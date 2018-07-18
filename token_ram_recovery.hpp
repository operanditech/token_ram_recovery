#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

#include <string>

namespace eosiosystem {
   class system_contract;
}

namespace eosio {

   using std::string;

   class token : public contract {
      public:
         using contract::contract;

         //@abi action
         void destroytoken( string symbol );

         //@abi action
         void destroyacc( string symbol, account_name acc );

      private:
         //@abi table accounts i64
         struct account {
            asset    balance;

            uint64_t primary_key()const { return balance.symbol.name(); }
         };

         //@abi table stat i64
         struct token_stats {
            asset          supply;
            asset          max_supply;
            account_name   issuer;

            uint64_t primary_key()const { return supply.symbol.name(); }
         };

         typedef eosio::multi_index<N(accounts), account> accounts;
         typedef eosio::multi_index<N(stat), token_stats> stats;
   };
} /// namespace eosio
