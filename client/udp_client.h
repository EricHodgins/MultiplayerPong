#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <iostream>
#include <string>
#include "../shared/cplatform.h"

class UDPClient {
    
    public:
        void ConnectToServer();
        void SendRDYToServer();
        void SendPaddlePositionToServer();
        void UpdateBallPosition();
        void UpdateOpponentPaddlePosition();

    private:

};

#endif
