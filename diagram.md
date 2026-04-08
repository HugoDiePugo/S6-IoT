```mermaid
architecture-beta
    service db(database)[Database]
    service dash(cloud)[DashBoard]
    service nodered(server)[NodeRed]
    service network(internet)[TTN]
    service micro(disk)[SFFA]
    junction dbJ
    
    db:B--T:dbJ
    dbJ:B -- T:dash
    dbJ:L -- R:nodered
    %% nodered:T -- L:dash
    nodered:L -- R:network
    network:L -- R:micro
```
    
