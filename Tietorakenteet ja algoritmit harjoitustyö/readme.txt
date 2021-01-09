Node-struct tietorakennetta käytettiin siksi, että pystyttiin tekemään graafeja ja käyttämään leveyteen ja syvyyteen ensin hakuja.
Reittejä ja solmuja säilytettiin unordered_mapissa, koska niiden ei tarvitse olla järjestyksessä ja asioiden hakeminen on sieltä keskimäärin vakioaikaista ja simppeliä.
Node-structin sisällä on käytetty unordered_mappia samasta syystä kuin reittejen ja solmujen säilyttämisen kohdalla. Multimappia käytettiin sen paremman soveltuvuuden takia.
Journey_earliest_arrival ei toimi täysin oikein.
