# Timez

A *Timez* is a binary representation for time stamps encoded in a 64 bit signed 
integer. It contains 

1. the number of micro seconds elapsed since a reference time called the *epoch*, 
2. the time offset to the UTC time in the location where the stamp was generated.

The epoch is the 1 January 1970 00:00:00 UTC. The *Timez* time stamp is intended
to be transmitted accross internet between locations with a different time offset 
relative to the UTC time. No time value before the *epoch* can be represented by
*Timez*.

Note: the *z* of *Timez* has no relation to the military *Zulu* term used to
identify the UTC time.


## Encoding

<pre>
   64                     12        0   bits
   |__________  __________|________|
   |__________//__________|________|
   |nbr µs since UTC epoch| offset |
</pre>

+ The 52 most significant bits is a signed integer in two's complement encoding 
   the number of microseconds elapsed since the reference time called *epoch* 
   subtracted by 2^52 ;
+ The epoch is the `1 January 1970 00:00:00 UTC` ;
+ The 12 less significant bits is an unsigned integer encoding the local time
   offset (including day time saving) in minutes plus 2048 ;
+ The value is invalid when the 12 less significant bits are all 0 ;

## Properties

* the covered time range is 1970 to 1970 + 142 years ;
* the time resolution is in microseconds ;
* the covered time offset range is +/- 34 hours ;
* the time offset resolution is in minutes ;
* the time offset is the sum of the time zone offset and day light saving time ; 
* comparing the 64 bit signed integer is equivalent to UTC time comparison ;
* the 64 bit integer value 0 can be use as undefined or invalid time stamp value ;
* the local time of the stamp producer can be deduced using the contained time 
   offset information ;
* not subject to leap seconds adjustement or day light saving time changes ;
* not exposed to the year 2038 problem where actual `time_t` will wrap ;
* a *Timez* is stored in a database as a 64 bit signed integer ;
    * thi integer ordering is the same as the UTC time ordering ;
    * selection by UTC time range can be used ;
    * existing data type can be used ;

## Discussion

ISO 8601 defines an international standad ASCII representation of date and time 
including the time offset information. It is designed to allow sorting by time 
with a  lexical ordering. Unfortunately, the encoded time is the local time. 
This representation is thus not appropriate when comparing times with different 
offsets. A prior conversion in UTC time is required. 

The glibc and Unix use a signed integer (`time_t`) with a resolution of seconds. 
The time zone information with day light saving is stored in different variables.

The integer value is the number of seconds elapsed since the 
`1 January 1970 00:00:00 UTC`. Unfortunately the value will wrap to a negative 
number the 19 January 1938. This is known as the year 2038 problem.

The function `gettimeofday()` or the preferred `clock_gettime()` function 
returns also a `time_t` value and a `long signed integer` providing the 
nanoseconds elapsed. This value is subject to the same year 2038 problem.

Microsoft has promoted the use of a `double float` value to store time in second 
units. A double has 52 bit mantissa and 11 bits exponent. While the value range 
it may represent is very large, it can't accurately represent fractions of 
seconds. It also doesn't provide a time zone information.

## Code

The code is embryonic and simply a proof of concept. Use the following command to build the simple test program.

    gcc -lrt main.c timez.c

## Reference

+ Wikipedia [ISO 8601](https://en.wikipedia.org/wiki/ISO_8601) (english)
+ Wikipedia [ISO 8601](https://fr.wikipedia.org/wiki/ISO_8601) (frensh)
+ [Summary of ISO 8601](http://www.cl.cam.ac.uk/~mgk25/iso-time.html) (english)
+ [RFC 3339](https://tools.ietf.org/html/rfc3339)
+ [Year 2038 problem](https://en.wikipedia.org/wiki/Year_2038_problem)
+ [IANA time zone](http://www.iana.org/time-zones)
