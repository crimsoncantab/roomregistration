# Version Control #
We'll just use this Google code website to maintain versions of our code.

# Development #
Develop pretty much however you want to. Loren is using Netbeans to develop the code and FTP it to his FAS account for testing.  On FAS account, ftp code into public\_html/ and execute fixwebfiles in public\_html/ to fix permissions.

# MySQL #
Should we use the databases we got for the class?  Seems like the easiest solution.  Should we develop with our separate databases, then?  In that case, we want some SQL scripts for our schema definition (suffix .ddl) and to input test data (suffix .sql).

# PHP #
PHP scripts need to have .cgi extension and be shebanged "#!/usr/local/bin/php".  This will work in NICE (notice that included files/.inc that are used via require() or include() don't need shebanging).