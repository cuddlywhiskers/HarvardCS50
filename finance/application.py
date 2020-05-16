import os
from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # variables
    index = []
    total_value = 0

    # get all transactions
    all_stocks = db.execute("SELECT ticker, SUM(share) AS shares FROM transactions WHERE username = :username GROUP BY ticker",
                        username = session["user_id"])

    for s in all_stocks:
        stock = {}
        if s["shares"] > 0:
            stock["ticker"] = s["ticker"]
            stock["company"] = lookup(s["ticker"])["name"]
            stock["share"] = int(s["shares"])
            stock["price"] = round(lookup(s["ticker"])["price"],2)
            stock["total"] = round(lookup(s["ticker"])["price"],2) * int(s["shares"])
            total_value += round(lookup(s["ticker"])["price"],2) * int(s["shares"])

        index.append(stock)

    # get current amount
    cash = db.execute("SELECT cash FROM users WHERE username = :username",
                    username = session["user_id"])
    remaining_cash = cash[0]["cash"]
    total_value += remaining_cash

    return render_template("index.html", all_stocks=index, remaining=remaining_cash, total=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == 'POST':
        info = lookup(request.form.get("symbol"))
        ticker = info["symbol"]
        price = info["price"]
        stock = int(request.form.get("buy_share"))

        # get cash amount from users
        rows = db.execute("SELECT cash FROM users WHERE username = :username",
                          username=session["user_id"])

        for row in rows:
            cash = int(row["cash"])

        # validate whether whether ticker is valid
        if not info:
            return apology("must provide valid ticker", 403)

        elif cash < (price * stock):
            return apology("insufficient funds to proceed", 403)


        # update table upon successful purchase
        remaining = cash - (price * stock)
        date_of_transaction = datetime.datetime.now()

        db.execute("INSERT INTO transactions (username, date, ticker, share, price) VALUES (?, ?, ?, ?, ?)",
                session["user_id"], date_of_transaction, ticker, stock, price)
        db.execute("UPDATE users SET cash = :cash WHERE username = :username",
                    cash = remaining, username = session["user_id"])

    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    history = db.execute("SELECT ticker, share, price, date FROM transactions WHERE username = :username ORDER BY date",
                        username = session["user_id"])

    return render_template("history.html", history = history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["username"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # look up the stocks
    if request.method == 'GET':
        return render_template("quote.html")

    # submit the stock
    else:
        info = lookup(request.form.get("ticker"))

        if not info:
            return apology("must provide valid ticker", 403)

        else:
            return render_template("quotation.html", info=info)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # submit registration via POST
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        repeated_pass = request.form.get("repeat_password")

        # Check for user
        if not username:
            return apology("must provide username", 403)

        # Check password
        elif not password:
            return apology("must provide password", 403)

        # check whether passwords are same
        elif password != repeated_pass:
            return apology("please provide same password", 403)

        # Check for validity of username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=username)

        if len(rows) == 1:
            return apology("username in use", 403)

        # insert new user into table
        else:
            encrypted = generate_password_hash(password)
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                        username, encrypted)
            return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():

    #  get user's portfolio
    portfolio = db.execute("SELECT ticker, SUM(share) as shares FROM transactions WHERE username = :username GROUP BY ticker",
                        username = session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE username = :username",
                    username = session["user_id"])

    if request.method == "POST":
        # variables
        ticker = request.form.get("symbol")
        share = int(request.form.get("sell_share"))
        price = lookup(ticker)["price"]
        date_of_transaction = datetime.datetime.now()

        # determine whether number of stocks keyed in are more than actual stocks
        if [stocks for stocks in portfolio if stocks["ticker"] == ticker][0]["shares"] < share:
            return apology("Unable to proceed", 403)

        # update total amount left
        for c in cash:
            user_amount = c["cash"]

        sold_shares = -1 * share
        total_amount = (share * price) + user_amount

        # if success, update transaction
        db.execute("INSERT INTO transactions (username, date, ticker, share, price) VALUES (?, ?, ?, ?, ?)",
            session["user_id"], date_of_transaction, ticker, sold_shares, price)
        db.execute("UPDATE users SET cash = :cash WHERE username = :username",
            cash = total_amount, username = session["user_id"])

        return redirect("/")

    else:
        return render_template("sell.html", dropdown = portfolio, lookup = lookup)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
