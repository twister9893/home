#ifndef LIBENUM_H
#define LIBENUM_H

enum FieldType {
    Integer = 0,
    Real,
    Scalable,
    Enumeration,
    Constant,
    Boolean,
    String,
    Unused
};

enum FieldDimension {
    Meters = 0,
    kMeters,
    Miles,
    MetersPerSecond,
    Knots,
    Seconds,
    mcSeconds,
    Degrees,
    TD,
    Radians,
    No
};

enum EnumerationHeaderSection {
    Code = 0,
    Acronym,
    Transcript
};

enum FormularHeaderSection {
    Size = 0,
    Type,
    Name,
    Description
};

#endif // LIBENUM_H
