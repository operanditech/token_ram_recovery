# Token RAM Recovery

An EOSIO smart contract for deleting created tokens and their account balances.

If you've created a token using the standard `eosio.token` or a compatible version of it,
you can deploy this contract to the account in order to delete the token from the `stat`
table and the account balances of the token from the `accounts` table using the `destroytoken`
and `destroyacc` actions respectively. This way you can reclaim your RAM to use it on other things.

**More info here:** https://eosio.stackexchange.com/a/1535/1834
