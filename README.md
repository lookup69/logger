# logger

a utility for logging


    msg ---- LoggerPlugin ---> log

    LoggerPlugin:
        FileLogPlugin -> log to file
        ConsoleLogPlugin -> disply to console 
        unixSocketLogPlugin -> send log to unix socket
