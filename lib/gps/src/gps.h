#ifndef GPS_H
#define GPS_H
    extern double lat, lng, alt;
    extern int sat, hdop, datevalue;
    extern long distanceToLast;
    extern time_t unix_timestamp;
    void gpsinit();
    void smartDelay(unsigned long ms);
    void gpsgetdata();

#endif