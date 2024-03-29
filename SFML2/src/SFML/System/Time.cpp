////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2009 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/System/Time.hpp>


namespace sf
{
////////////////////////////////////////////////////////////
const Time Time::Zero;


////////////////////////////////////////////////////////////
Time::Time() :
myMicroseconds(0)
{
}


////////////////////////////////////////////////////////////
float Time::AsSeconds() const
{
    return myMicroseconds / 1000000.f;
}


////////////////////////////////////////////////////////////
Int32 Time::AsMilliseconds() const
{
    return static_cast<Uint32>(myMicroseconds / 1000);
}


////////////////////////////////////////////////////////////
Int64 Time::AsMicroseconds() const
{
    return myMicroseconds;
}


////////////////////////////////////////////////////////////
Time::Time(Int64 microseconds) :
myMicroseconds(microseconds)
{
}


////////////////////////////////////////////////////////////
Time Seconds(float amount)
{
    return Time(static_cast<Uint64>(amount * 1000000));
}


////////////////////////////////////////////////////////////
Time Milliseconds(Int32 amount)
{
    return Time(static_cast<Uint64>(amount) * 1000);
}


////////////////////////////////////////////////////////////
Time Microseconds(Int64 amount)
{
    return Time(amount);
}


////////////////////////////////////////////////////////////
bool operator ==(const Time& left, const Time& right)
{
    return left.AsMicroseconds() == right.AsMicroseconds();
}


////////////////////////////////////////////////////////////
bool operator !=(const Time& left, const Time& right)
{
    return left.AsMicroseconds() != right.AsMicroseconds();
}


////////////////////////////////////////////////////////////
bool operator <(const Time& left, const Time& right)
{
    return left.AsMicroseconds() < right.AsMicroseconds();
}


////////////////////////////////////////////////////////////
bool operator >(const Time& left, const Time& right)
{
    return left.AsMicroseconds() > right.AsMicroseconds();
}


////////////////////////////////////////////////////////////
bool operator <=(const Time& left, const Time& right)
{
    return left.AsMicroseconds() <= right.AsMicroseconds();
}


////////////////////////////////////////////////////////////
bool operator >=(const Time& left, const Time& right)
{
    return left.AsMicroseconds() >= right.AsMicroseconds();
}


////////////////////////////////////////////////////////////
Time operator -(const Time& right)
{
    return Microseconds(-right.AsMicroseconds());
}


////////////////////////////////////////////////////////////
Time operator +(const Time& left, const Time& right)
{
    return Microseconds(left.AsMicroseconds() + right.AsMicroseconds());
}


////////////////////////////////////////////////////////////
Time& operator +=(Time& left, const Time& right)
{
    return left = left + right;
}


////////////////////////////////////////////////////////////
Time operator -(const Time& left, const Time& right)
{
    return Microseconds(left.AsMicroseconds() - right.AsMicroseconds());
}


////////////////////////////////////////////////////////////
Time& operator -=(Time& left, const Time& right)
{
    return left = left - right;
}


////////////////////////////////////////////////////////////
Time operator *(const Time& left, float right)
{
    return Seconds(left.AsSeconds() * right);
}


////////////////////////////////////////////////////////////
Time operator *(const Time& left, Int64 right)
{
    return Microseconds(left.AsMicroseconds() * right);
}


////////////////////////////////////////////////////////////
Time operator *(float left, const Time& right)
{
    return right * left;
}


////////////////////////////////////////////////////////////
Time operator *(Int64 left, const Time& right)
{
    return right * left;
}


////////////////////////////////////////////////////////////
Time& operator *=(Time& left, float right)
{
    return left = left * right;
}


////////////////////////////////////////////////////////////
Time& operator *=(Time& left, Int64 right)
{
    return left = left * right;
}


////////////////////////////////////////////////////////////
Time operator /(const Time& left, float right)
{
    return Seconds(left.AsSeconds() / right);
}


////////////////////////////////////////////////////////////
Time operator /(const Time& left, Int64 right)
{
    return Microseconds(left.AsMicroseconds() / right);
}


////////////////////////////////////////////////////////////
Time& operator /=(Time& left, float right)
{
    return left = left / right;
}


////////////////////////////////////////////////////////////
Time& operator /=(Time& left, Int64 right)
{
    return left = left / right;
}

} // namespace sf
