#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>

int main(int argc, char *argv[]) {
    pid_t pid, sid;

    // 1 - Fork
    pid = fork(); 

    if (pid < 0) 
    {
        exit(EXIT_FAILURE);
    }
    if (pid > 0) 
    {
        exit(EXIT_SUCCESS);
    }

    //2 - Umask
    umask(0);

    //3 - Logs
    openlog(argv[0],LOG_NOWAIT|LOG_PID,LOG_USER); 
    syslog(LOG_NOTICE, "Successfully started daemon\n"); 

    //4 - Session Id
    sid = setsid();
    if (sid < 0) {
        syslog(LOG_ERR, "Could not create process group\n");
        exit(EXIT_FAILURE);
    }

    //5 - WD
    if ((chdir("/")) < 0) {
        syslog(LOG_ERR, "Could not change working directory to /\n");
        exit(EXIT_FAILURE);
    }

    //6 - FD
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    // Il cuore del nostro deamon:
    while (1) {
        syslog(LOG_INFO, "I'm alive\n");
        sleep(15);
    }

    // Quando il nostro deamon ha finito il suo lavoro:
    closelog();
}
