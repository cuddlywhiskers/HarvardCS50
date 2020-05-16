# Harvard CS50x 2020 Track: Web

[Problem Statement](https://cs50.harvard.edu/x/2020/tracks/web/finance/)

In finance, users are tasked to build a basic website that facilitates stock transactions and extract real time stock data from IEX. The following functions were then implemented:
- [x] register: allow new users to register for an account via html form and store these new information into the database. Each new user is also given default USD $10 000.
- [x] quote: allow users to look up for a stock's current price by keying in the stock ticker symbol.
- [x] buy: allow users to purchase stocks 
- [x] index: users to view their portfolio
- [x] sell: enable users to sell the share of stocks
- [x] history: allow users to view all transactions. 

2 tables were created within finance.db:
 - users: view of all users registered, username, password and remaining cash they have. 
 - transactions: view of all transactions pertinent to a particular stock, date of transaction and price at which it was transacted. 
 
 
 ---
 Apart from 6 functions, the remaining codes were written by the CS50 staff. 
