/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include "token_ram_recovery.hpp"

namespace eosio {

void token::destroytoken( string symbol )
{
    require_auth( _self );

    symbol_type sym = string_to_symbol(0, symbol.c_str());

    stats statstable( _self, sym.name() );
    auto existing = statstable.find( sym.name() );
    eosio_assert( existing != statstable.end(), "token with symbol does not exist" );

    statstable.erase( existing );
}

void token::destroyacc( string symbol, account_name acc)
{
    require_auth( _self );

    symbol_type sym = string_to_symbol(0, symbol.c_str());

    accounts acctable( _self, acc );
    const auto& row = acctable.get( sym.name(), "no balance object found for provided account and symbol" );
    acctable.erase( row );
}

} /// namespace eosio

EOSIO_ABI( eosio::token, (destroytoken)(destroyacc) )
