// Copyright (c) 2005-2011 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD, an XML Schema to
// C++ data binding compiler.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
// In addition, as a special exception, Code Synthesis Tools CC gives
// permission to link this program with the Xerces-C++ library (or with
// modified versions of Xerces-C++ that use the same license as Xerces-C++),
// and distribute linked combinations including the two. You must obey
// the GNU General Public License version 2 in all respects for all of
// the code used other than Xerces-C++. If you modify this copy of the
// program, you may extend this exception to your version of the program,
// but you are not obligated to do so. If you do not wish to do so, delete
// this exception statement from your version.
//
// Furthermore, Code Synthesis Tools CC makes a special exception for
// the Free/Libre and Open Source Software (FLOSS) which is described
// in the accompanying FLOSSE file.
//

#include <xsd/cxx/pre.hxx>

// Begin prologue.
//
//
// End prologue.

#include "generatorType.hxx"

namespace Atom
{
  // generatorType
  // 

  const generatorType::uri_optional& generatorType::
  uri () const
  {
    return this->uri_;
  }

  generatorType::uri_optional& generatorType::
  uri ()
  {
    return this->uri_;
  }

  void generatorType::
  uri (const uri_type& x)
  {
    this->uri_.set (x);
  }

  void generatorType::
  uri (const uri_optional& x)
  {
    this->uri_ = x;
  }

  void generatorType::
  uri (::std::auto_ptr< uri_type > x)
  {
    this->uri_.set (x);
  }

  const generatorType::version_optional& generatorType::
  version () const
  {
    return this->version_;
  }

  generatorType::version_optional& generatorType::
  version ()
  {
    return this->version_;
  }

  void generatorType::
  version (const version_type& x)
  {
    this->version_.set (x);
  }

  void generatorType::
  version (const version_optional& x)
  {
    this->version_ = x;
  }

  void generatorType::
  version (::std::auto_ptr< version_type > x)
  {
    this->version_.set (x);
  }

  const generatorType::base_optional& generatorType::
  base () const
  {
    return this->base_;
  }

  generatorType::base_optional& generatorType::
  base ()
  {
    return this->base_;
  }

  void generatorType::
  base (const base_type& x)
  {
    this->base_.set (x);
  }

  void generatorType::
  base (const base_optional& x)
  {
    this->base_ = x;
  }

  void generatorType::
  base (::std::auto_ptr< base_type > x)
  {
    this->base_.set (x);
  }

  const generatorType::lang_optional& generatorType::
  lang () const
  {
    return this->lang_;
  }

  generatorType::lang_optional& generatorType::
  lang ()
  {
    return this->lang_;
  }

  void generatorType::
  lang (const lang_type& x)
  {
    this->lang_.set (x);
  }

  void generatorType::
  lang (const lang_optional& x)
  {
    this->lang_ = x;
  }

  void generatorType::
  lang (::std::auto_ptr< lang_type > x)
  {
    this->lang_.set (x);
  }
}

#include <xsd/cxx/xml/dom/parsing-source.hxx>

#include <xsd/cxx/tree/type-factory-map.hxx>

namespace _xsd
{
  static
  const ::xsd::cxx::tree::type_factory_plate< 0, char >
  type_factory_plate_init;
}

namespace Atom
{
  // generatorType
  //

  generatorType::
  generatorType ()
  : ::xml_schema::string (),
    uri_ (this),
    version_ (this),
    base_ (this),
    lang_ (this)
  {
  }

  generatorType::
  generatorType (const char* _xsd_string_base)
  : ::xml_schema::string (_xsd_string_base),
    uri_ (this),
    version_ (this),
    base_ (this),
    lang_ (this)
  {
  }

  generatorType::
  generatorType (const ::std::string& _xsd_string_base)
  : ::xml_schema::string (_xsd_string_base),
    uri_ (this),
    version_ (this),
    base_ (this),
    lang_ (this)
  {
  }

  generatorType::
  generatorType (const ::xml_schema::string& _xsd_string_base)
  : ::xml_schema::string (_xsd_string_base),
    uri_ (this),
    version_ (this),
    base_ (this),
    lang_ (this)
  {
  }

  generatorType::
  generatorType (const generatorType& x,
                 ::xml_schema::flags f,
                 ::xml_schema::container* c)
  : ::xml_schema::string (x, f, c),
    uri_ (x.uri_, f, this),
    version_ (x.version_, f, this),
    base_ (x.base_, f, this),
    lang_ (x.lang_, f, this)
  {
  }

  generatorType::
  generatorType (const ::xercesc::DOMElement& e,
                 ::xml_schema::flags f,
                 ::xml_schema::container* c)
  : ::xml_schema::string (e, f | ::xml_schema::flags::base, c),
    uri_ (this),
    version_ (this),
    base_ (this),
    lang_ (this)
  {
    if ((f & ::xml_schema::flags::base) == 0)
    {
      ::xsd::cxx::xml::dom::parser< char > p (e, false, true);
      this->parse (p, f);
    }
  }

  void generatorType::
  parse (::xsd::cxx::xml::dom::parser< char >& p,
         ::xml_schema::flags f)
  {
    while (p.more_attributes ())
    {
      const ::xercesc::DOMAttr& i (p.next_attribute ());
      const ::xsd::cxx::xml::qualified_name< char > n (
        ::xsd::cxx::xml::dom::name< char > (i));

      if (n.name () == "uri" && n.namespace_ ().empty ())
      {
        this->uri_.set (uri_traits::create (i, f, this));
        continue;
      }

      if (n.name () == "version" && n.namespace_ ().empty ())
      {
        this->version_.set (version_traits::create (i, f, this));
        continue;
      }

      if (n.name () == "base" && n.namespace_ () == "http://www.w3.org/XML/1998/namespace")
      {
        this->base_.set (base_traits::create (i, f, this));
        continue;
      }

      if (n.name () == "lang" && n.namespace_ () == "http://www.w3.org/XML/1998/namespace")
      {
        this->lang_.set (lang_traits::create (i, f, this));
        continue;
      }
    }
  }

  generatorType* generatorType::
  _clone (::xml_schema::flags f,
          ::xml_schema::container* c) const
  {
    return new class generatorType (*this, f, c);
  }

  generatorType& generatorType::
  operator= (const generatorType& x)
  {
    if (this != &x)
    {
      static_cast< ::xml_schema::string& > (*this) = x;
      this->uri_ = x.uri_;
      this->version_ = x.version_;
      this->base_ = x.base_;
      this->lang_ = x.lang_;
    }

    return *this;
  }

  generatorType::
  ~generatorType ()
  {
  }

  static
  const ::xsd::cxx::tree::type_factory_initializer< 0, char, generatorType >
  _xsd_generatorType_type_factory_init (
    "generatorType",
    "http://www.w3.org/2005/Atom");
}

#include <istream>
#include <xsd/cxx/xml/sax/std-input-source.hxx>
#include <xsd/cxx/tree/error-handler.hxx>

namespace Atom
{
}

#include <ostream>
#include <xsd/cxx/tree/error-handler.hxx>
#include <xsd/cxx/xml/dom/serialization-source.hxx>

#include <xsd/cxx/tree/type-serializer-map.hxx>

namespace _xsd
{
  static
  const ::xsd::cxx::tree::type_serializer_plate< 0, char >
  type_serializer_plate_init;
}

namespace Atom
{
  void
  operator<< (::xercesc::DOMElement& e, const generatorType& i)
  {
    e << static_cast< const ::xml_schema::string& > (i);

    // uri
    //
    if (i.uri ())
    {
      ::xercesc::DOMAttr& a (
        ::xsd::cxx::xml::dom::create_attribute (
          "uri",
          e));

      a << *i.uri ();
    }

    // version
    //
    if (i.version ())
    {
      ::xercesc::DOMAttr& a (
        ::xsd::cxx::xml::dom::create_attribute (
          "version",
          e));

      a << *i.version ();
    }

    // base
    //
    if (i.base ())
    {
      ::xercesc::DOMAttr& a (
        ::xsd::cxx::xml::dom::create_attribute (
          "base",
          "http://www.w3.org/XML/1998/namespace",
          e));

      a << *i.base ();
    }

    // lang
    //
    if (i.lang ())
    {
      ::xercesc::DOMAttr& a (
        ::xsd::cxx::xml::dom::create_attribute (
          "lang",
          "http://www.w3.org/XML/1998/namespace",
          e));

      a << *i.lang ();
    }
  }

  static
  const ::xsd::cxx::tree::type_serializer_initializer< 0, char, generatorType >
  _xsd_generatorType_type_serializer_init (
    "generatorType",
    "http://www.w3.org/2005/Atom");
}

// Begin epilogue.
//
//
// End epilogue.

#include <xsd/cxx/post.hxx>
