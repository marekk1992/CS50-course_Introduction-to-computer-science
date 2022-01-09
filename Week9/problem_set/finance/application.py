import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
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
    user_id = session['user_id']
    user_info = db.execute("SELECT * FROM users WHERE id=?", user_id)
    user_cash = user_info[0]['cash']
    total_cash = user_cash
    
    user_stocks = db.execute("SELECT * FROM owned_stocks WHERE user_id=?", user_id)
    
    if user_stocks:
        number_of_stocks = db.execute("SELECT COUNT(id) FROM owned_stocks WHERE user_id=?", user_id)[0]['COUNT(id)']
    
        total_stocks_value = 0
        
        for i in range(number_of_stocks):
            total_stocks_value += user_stocks[i]['total_price']
    
        total_cash = user_cash + total_stocks_value
        
        return render_template("index.html", user_stocks=user_stocks, user_info=user_info, user_cash=user_cash, total_cash=total_cash)
    
    else:
        return render_template("index.html", user_stocks=None, user_info=user_info, user_cash=user_cash, total_cash=total_cash)

    
@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        
        selected_symbol = request.form.get("symbol")
        result = lookup(selected_symbol)
        
        if not selected_symbol or result == None:
            return apology("Please provide a valid symbol", 400)
        
        number_of_shares = request.form.get("shares")
        if not number_of_shares.isnumeric():
            return apology("Please provide a valid share number", 400)

        number_of_shares = int(number_of_shares)
            
        if number_of_shares <= 0:
            return apology("Please provide positive integer", 400)
            
        symbol = result.get('symbol')
        name = result.get('name')
        stock_price = result.get('price')
        total_price = stock_price * number_of_shares
        user_id = session['user_id']
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
        
        if user_cash < total_price:
            return apology("Insufficient funds", 403)
        
        operation = 'purchase'
        operation_time = datetime.datetime.now()
        timestamp = (operation_time.strftime("%Y-%m-%d %H:%M:%S"))
        db.execute("INSERT INTO transactions (symbol, stocks, stock_price, total_price, operation, transacted, user_id) VALUES (?, ?, ?, ?, ?, ?, ?)", 
                   symbol, number_of_shares, stock_price, total_price, operation, timestamp, user_id)
        
        cash_left = user_cash - total_price
        db.execute("UPDATE users SET cash=? WHERE id=?", cash_left, user_id)
        
        user_stocks = db.execute("SELECT * FROM owned_stocks WHERE user_id=? and symbol=?", user_id, symbol)
        if not user_stocks:
            db.execute("INSERT INTO owned_stocks (symbol, name, stocks, stock_price, total_price, user_id) VALUES (?, ?, ?, ?, ?, ?)", 
                       symbol, name, number_of_shares, stock_price, total_price, user_id)
        else:
            shares = user_stocks[0]['stocks'] + number_of_shares
            price = user_shares[0]['total_price'] + total_price
            stock_price = price / shares
            db.execute("UPDATE owned_stocks SET stocks=?, stock_price=?, total_price=? WHERE user_id=? and symbol=?", 
                       shares, stock_price, price, user_id, symbol)
        
        flash('Bought!')
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session['user_id']
    transactions = db.execute("SELECT * FROM transactions WHERE user_id=?", user_id)
    
    return render_template("history.html", transactions=transactions)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

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
    if request.method == "POST":
        
        provided_symbol = request.form.get("symbol")
        
        if not provided_symbol:
            return apology("please input a symbol", 400)
        
        result = lookup(provided_symbol)
        if result == None:
            return apology("please input a valid symbol", 400)
        
        name = result.get('name')
        words = name.split(" ")
        word1 = words[0]
        word2 = words[1]
        symbol = result.get('symbol')
        stock_price = result.get('price')
    
        return render_template("quoted.html", name1=word1, name2=word2, symbol=symbol, stock_price=stock_price)
        
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        
        username = request.form.get("username")
        
        if not username:
            return apology("must provide username", 400)
            
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) == 1:
            return apology("username already exists", 400)
        
        password = request.form.get("password")
            
        if not password:
            return apology("must provide password", 400)
        
        if len(password) < 4:
            return apology("password lenght should be at least 4 characters", 400)
        
        if len(password) > 8:
            return apology("maximum number of characters in password is 8", 400)
        
        numbers = sum(number.isdigit() for number in password)
        if numbers < 1:
            return apology("password should contain at least 1 number", 400)
            
        if not any(upper_letter.isupper() for upper_letter in password):
            return apology("password must contain at least 1 upper case letter", 400)
        
        confirmation_password = request.form.get("confirmation")
            
        if confirmation_password != password:
            return apology("passwords do not match", 400)
        
        hash_code = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
        db.execute("INSERT into users (username, hash) VALUES (?, ?)", username, hash_code)
            
        return render_template("login.html")
        
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session['user_id']
    user_stocks = db.execute("SELECT * FROM owned_stocks WHERE user_id=?", user_id)
  
    if request.method == "POST":
        stock_symbol = request.form.get("symbol")
        if not stock_symbol:
            return apology("failed to select a stock", 403)
            
        owned_stocks = db.execute("SELECT stocks FROM owned_stocks WHERE symbol=? and user_id=?", stock_symbol, user_id)
        
        if owned_stocks == None:
            return apology("You don`t own any shares of this stock", 400)
        
        number_of_shares = request.form.get("shares")
        if not number_of_shares:
            return apology("Please provide number of stocks", 400)
        
        if not number_of_shares.isnumeric():
            return apology("Please provide a valid share number", 400)
            
        number_of_shares = int(number_of_shares)
            
        if number_of_shares <= 0:
            return apology("Please provide positive integer", 400)
        
        my_shares = owned_stocks[0]['stocks']
        
        if number_of_shares > my_shares:
            return apology("You don`t own that many shares of this stock", 400)
            
        result = lookup(stock_symbol)
        symbol = result.get('symbol')
        current_stock_price = result.get('price')
        total_price = current_stock_price * number_of_shares
        
        sold_shares = number_of_shares * (-1)
        operation = 'sell'
        operation_time = datetime.datetime.now()
        timestamp = (operation_time.strftime("%Y-%m-%d %H:%M:%S"))
        
        db.execute("INSERT INTO transactions (symbol, stocks, stock_price, total_price, operation, transacted, user_id) VALUES (?, ?, ?, ?, ?, ?, ?)", 
                   symbol, sold_shares, current_stock_price, total_price, operation, timestamp, user_id) 
        
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]['cash']
        cash_left = user_cash + total_price
        db.execute("UPDATE users SET cash=? WHERE id=?", cash_left, user_id)
        
        my_shares = db.execute("SELECT * FROM owned_stocks WHERE user_id=? and symbol=?", user_id, symbol)
        shares = my_shares[0]['stocks'] - number_of_shares
        if shares <= 0:
            db.execute("DELETE FROM owned_stocks WHERE user_id=? and symbol=?", user_id, symbol)
        else:
            price = my_shares[0]['total_price'] - total_price
            share_price = price / shares
            db.execute("UPDATE owned_stocks SET stocks=?, stock_price=?, total_price=? WHERE user_id=? and symbol=?", 
                       shares, share_price, price, user_id, symbol)
        
        flash('Sold!')
        return redirect("/")
        
    else:
        return render_template("sell.html", user_stocks=user_stocks)
        

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)