========
Kairopak
========
kairopak is the system and packet manager for the Kairo kernel

* components
** kp-manager
    Main component, manages services
** kp-controller
    The controller, controlls and configures the kp-manager and everything else
** kp-recorder
    System logger, logs events in binary format
** kp-syncronizer
    Syncronizes the time, and any other external data
** kp-usrset
    Manages the user layer, like keymapping, hostname, user-datas
** kp-endecoder
    Manages passwords, cryptography, and any other encoding, decoding or privat stuff
** kp-networkmgers
    Manages the network
** kp-link
    IPC
** kp-shell
    user-shell

* System Communication Protocol schema
    message("from" "to" "timestamp" "type1" "type2" "message")
    from        the sender servery or address
    to          the reciever servery or address
    timestamp   timestamp in YY:MM:DD,HH:MM:SS:MSMS format
    type1       region, can be: hardware, bootphase, kernel, kp, root, user
    type2       state, can be: INFO DATA ERRO WARN SUCC FAIL OTHE
    message     message

