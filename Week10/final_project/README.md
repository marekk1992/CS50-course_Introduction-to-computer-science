# Movies and TV-shows wathclist
#### Video Demo:  <https://youtu.be/yklF-xsbJxM>
#### Description: This web application allows users to create their own watchlist of movies/TV-shows, sort them by various categories and add new titles.

**application.py** - does main functions of web application. Registers users by saving user data into *users* table in *watchlist.db*. Logges user in after checking for existing user data. Remembers user session. Creates ability to add new titles into *movies* table. Renders various templates according to html's requests and redirects to different routes. 

**helpers.py** - stores additional functions, which are called in main program. Function *login_required* - decorates routes to require loggin. Function *error* - renders error message if there is server error or some of application requirements are not met.

**watchlist.db** - database has two tables: *users* - stores user data: username and password hash generated using *werkzeug.security library*, *movies* - stores movies data: title, description, release year and user rating. This table has foreign key, which is *user_id* from *users* table.

**requirements.txt** - requirements of flask framework for this project, which include: *cs50*, *Flask*, *Flask-Session*, *requests*.

**layaout.html** - defines main layout of the all pages of web application. If user is logged-in it shows home page of application, otherwise - log-in page.

**login.html** - creates ability to log-in by inputting *username* and *password*. Login is enabled by checking for submitted *username* and *password* in *users table* from *watchlist.db*. From login page you can switch to *register* page.

**register.html** - creates ability to create new user by inputting *username*, *password* and *confirmation password*. If user is registered succesfully, *username*, *hashed password* are stored in *users table* in *watchlist.db*. Also from register page you can switch to **login** page.

**home.html** - main page of web application, where you can see which user is currently logged-in, log-out and add new title to your watchlist.

**add.html** - creates ability to add new title to watchlist by adding its *title*, *description*, *release year* and *user rating*. 

**error.html** - renders error message with appropriate error code if some of requirements in any of pages are not met or error appears.