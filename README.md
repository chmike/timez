# Timez

Timez is a binary representation for time and time zone offset combined in a 64 bit signed integer. The time is encoded as the microseconds elapsed since an epoch, and the time offset as the sum of the time zone offset and the day light saving time offset. 

<pre>
   64                    11        0   bits
   |__________  __________|________|
   |__________//__________|________|
   | µs count since epoch | tz+1024|
</pre>

+ The 53 most significant bits is a signed integer in two's complement encoding the number of microseconds elapsed since the reference time called *epoch* ;
+ The epoch is the `1 January 2040 00:00:00 UTC` ;
+ The 11 less significant bits is an unsigned integer encoding the time offset in minutes plus 1024 ;
+ The time offset is the sum of the time zone offset and the day light saving ;
+ The timez value is undefined when the 11 less significant bits are all 0 ;

The current implementation uses the epoch `1 January 1970 00:00:00 UTC` to use standard glibc code to convert the `timez` in its date and time components. But ideally, the epoch should be set to 2040 because 2040 - 142,7 ~= 1970 - 68.

## Properties

* the covered time range is +/- 142 years relative to the epoch ;
* the time resolution is microseconds ;
* the covered time offset range is +/- 17:00 ;
* the time offset resolution is minutes ;
* comparing the 64 bit signed integer is equivalent to UTC time comparison ;
* the 64 bit integer 0 is an invalid `timez` value ;
* invalid `timez` values can be used as undefined `timez` value ;
* the local time can be deduced using the contained time offset information ;
* not subject to leap seconds adjustement or day light saving time changes ;
* not exposed to the year 2038 problem where actual `time_t` will wrap ;
* a `timez` stored in a database as a 64 bit signed integer ;
    * will be sorted or indexed by UTC time ;
    * selection by UTC time range can be used ;
    * existing data type can be used ;

## Discussion

ISO 8601 defines an international standad ASCII representation of date and time including the time offset information. It is designed to allow sorting by time with a  lexical ordering. Unfortunately, the encoded time is the local time. This representation is thus not appropriate when comparing times with different offsets. A prior conversion in UTC time is required. 

The glibc and Unix use a signed integer (`time_t`) with a resolution of seconds. The time zone information with day light saving is stored in different variables.

The integer value is the number of seconds elapsed since the `1 January 1970 00:00:00 UTC`. Unfortunately the value will wrap to a negative number the 19 January 1938. This is known as the year 2038 problem.

The function `gettimeofday()` or the preferred `clock_gettime()` function returns also a time_t value and a `long signed integer` providing the nanoseconds elapsed. This value is subject to the same year 2038 problem.

Microsoft has promoted the use of a `double float` value to store time in second units. A double has 52 bit mantissa and 11 bits exponent. While the value range it may represent is very large, it can't accurately represent fractions of seconds. It also doesn't provide a time zone information.

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
