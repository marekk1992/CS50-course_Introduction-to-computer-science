import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import error, login_required

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


# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)


# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///watchlist.db")


@app.route("/")
@login_required
def home():
    """Show user watchlist"""
    user_id = session['user_id']
    user_info = db.execute("SELECT * FROM users WHERE id=?", user_id)
    username = user_info[0]['username']
    
    titles = db.execute("SELECT * FROM movies WHERE user_id = ?", user_id)
    number_of_titles = len(titles)
    if number_of_titles > 0:
        return render_template("home.html", username=username, titles=titles, number_of_titles=number_of_titles)
    
    else:
        return render_template("home.html", username=username, titles=None, number_of_titles=number_of_titles)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        
        username = request.form.get("username")
        if not username:
            return error("Must provide username", 400)
            
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        if len(rows) == 1:
            return error("Username already exists", 400)
        
        password = request.form.get("password")
            
        if not password:
            return error("Must provide password", 400)
        
        if len(password) < 4:
            return error("Password lenght should be at least 4 characters", 400)
        
        numbers = sum(number.isdigit() for number in password)
        if numbers < 1:
            return error("Password should contain at least 1 number", 400)
            
        if not any(upper_letter.isupper() for upper_letter in password):
            return error("password must contain at least 1 upper case letter", 400)
        
        confirmation_password = request.form.get("confirmation_password")
        if confirmation_password != password:
            return error("Passwords do not match", 400)
        
        hash_code = generate_password_hash(password, method='pbkdf2:sha256', salt_length=8)
        db.execute("INSERT into users (username, hash) VALUES (?, ?)", username, hash_code)
            
        return render_template("login.html")
        
    else:
        return render_template("register.html")
    

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    if request.method == "POST":
        
        username = request.form.get("username")
        password = request.form.get("password")

        if not username:
            return error("Must provide username", 400)

        elif not password:
            return error("Must provide password", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
            return error("Invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    else:
        return render_template("login.html")
    
    
@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    """Add movie or TV-show to your watchlist"""
    user_id = session['user_id']
    user_info = db.execute("SELECT * FROM users WHERE id=?", user_id)
    username = user_info[0]['username']
    
    if request.method == "POST":
        
        title = request.form.get("title")
        if not title:
            return error("Please add movie/TV-show title", 400)
        
        description = request.form.get("description")
        if not description:
            return error("Please add description", 400)
            
        release_year = request.form.get("release_year")
        if not release_year.isnumeric():
            return error("Please provide a valid release year", 400)

        release_year = int(release_year)
        if release_year < 1895:
            return error("First official movie was released in 1895. Please provide a valid release year", 400)
            
        if release_year > 2025:
            return error("Please choose release year not greater than 2025", 400)
            
        user_rating = round(float((request.form.get("rating"))), 1)
        if not user_rating:
            return error("Please add rating", 400)
        
        if user_rating < 0 or user_rating > 10:
            return error("Please provide a valid rating", 400)

        date_added = datetime.datetime.now()
        timestamp = (date_added.strftime("%Y-%m-%d"))

        db.execute("INSERT INTO movies (title, description, release_year, user_rating, timestamp, user_id) VALUES (?, ?, ?, ?, ?, ?)", 
                   title, description, release_year, user_rating, timestamp, user_id)
        
        flash(title + " added to your watchlist!")
        
        return redirect("/")

    else:
        return render_template("add.html", username=username)
    
    
def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return error(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)