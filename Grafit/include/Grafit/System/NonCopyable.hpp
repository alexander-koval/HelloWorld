////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2014 Laurent Gomila (laurent.gom@gmail.com)
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

#ifndef SFML_NONCOPYABLE_HPP
#define SFML_NONCOPYABLE_HPP


class NonCopyable {
protected:

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    /// Because this class has a copy constructor, the compiler
    /// will not automatically generate the default constructor.
    /// That's why we must define it explicitly.
    ///
    ////////////////////////////////////////////////////////////
    NonCopyable() {}

private:

    ////////////////////////////////////////////////////////////
    /// \brief Disabled copy constructor
    ///
    /// By making the copy constructor private, the compiler will
    /// trigger an error if anyone outside tries to use it.
    /// To prevent NonCopyable or friend classes from using it,
    /// we also give no definition, so that the linker will
    /// produce an error if the first protection was inefficient.
    ///
    ////////////////////////////////////////////////////////////
    NonCopyable(const NonCopyable&);

    ////////////////////////////////////////////////////////////
    /// \brief Disabled assignment operator
    ///
    /// By making the assignment operator private, the compiler will
    /// trigger an error if anyone outside tries to use it.
    /// To prevent NonCopyable or friend classes from using it,
    /// we also give no definition, so that the linker will
    /// produce an error if the first protection was inefficient.
    ///
    ////////////////////////////////////////////////////////////
    NonCopyable& operator =(const NonCopyable&);
};


#endif


////////////////////////////////////////////////////////////
/// \class gf::NonCopyable
/// \ingroup system
///
/// This class makes its instances non-copyable, by explicitly
/// disabling its copy constructor and its assignment operator.
///
/// To create a non-copyable class, simply inherit from
/// gf::NonCopyable.
///
/// The type of inheritance (public or private) doesn't matter,
/// the copy constructor and assignment operator are declared private
/// in gf::NonCopyable so they will end up being inaccessible in both
/// cases. Thus you can use a shorter syntax for inheriting from it
/// (see below).
///
/// Usage example:
/// \code
/// class MyNonCopyableClass : gf::NonCopyable
/// {
///     ...
/// };
/// \endcode
///
/// Deciding whether the instances of a class can be copied
/// or not is a very important design choice. You are strongly
/// encouraged to think about it before writing a class,
/// and to use gf::NonCopyable when necessary to prevent
/// many potential future errors when using it. This is also
/// a very important indication to users of your class.
///
////////////////////////////////////////////////////////////
