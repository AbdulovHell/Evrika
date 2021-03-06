// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: SaveSettings.proto
#define PROTOBUF_USE_DLLS
#ifndef PROTOBUF_SaveSettings_2eproto__INCLUDED
#define PROTOBUF_SaveSettings_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3002000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3002000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
// @@protoc_insertion_point(includes)
namespace Evrika {
class ProgSettings;
class ProgSettingsDefaultTypeInternal;
extern ProgSettingsDefaultTypeInternal _ProgSettings_default_instance_;
class ProgSettings_BatColor;
class ProgSettings_BatColorDefaultTypeInternal;
extern ProgSettings_BatColorDefaultTypeInternal _ProgSettings_BatColor_default_instance_;
class ProgSettings_SignalLvlColor;
class ProgSettings_SignalLvlColorDefaultTypeInternal;
extern ProgSettings_SignalLvlColorDefaultTypeInternal _ProgSettings_SignalLvlColor_default_instance_;
class SettingPack;
class SettingPackDefaultTypeInternal;
extern SettingPackDefaultTypeInternal _SettingPack_default_instance_;
}  // namespace Evrika

namespace Evrika {

namespace protobuf_SaveSettings_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_SaveSettings_2eproto

// ===================================================================

class ProgSettings_BatColor : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:Evrika.ProgSettings.BatColor) */ {
 public:
  ProgSettings_BatColor();
  virtual ~ProgSettings_BatColor();

  ProgSettings_BatColor(const ProgSettings_BatColor& from);

  inline ProgSettings_BatColor& operator=(const ProgSettings_BatColor& from) {
    CopyFrom(from);
    return *this;
  }

  static const ProgSettings_BatColor& default_instance();

  static inline const ProgSettings_BatColor* internal_default_instance() {
    return reinterpret_cast<const ProgSettings_BatColor*>(
               &_ProgSettings_BatColor_default_instance_);
  }

  void Swap(ProgSettings_BatColor* other);

  // implements Message ----------------------------------------------

  inline ProgSettings_BatColor* New() const PROTOBUF_FINAL { return New(NULL); }

  ProgSettings_BatColor* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    PROTOBUF_FINAL;
  void CopyFrom(const ProgSettings_BatColor& from);
  void MergeFrom(const ProgSettings_BatColor& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  void DiscardUnknownFields();
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(ProgSettings_BatColor* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::std::string GetTypeName() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 colorLow = 1;
  void clear_colorlow();
  static const int kColorLowFieldNumber = 1;
  ::google::protobuf::int32 colorlow() const;
  void set_colorlow(::google::protobuf::int32 value);

  // int32 colorMid = 2;
  void clear_colormid();
  static const int kColorMidFieldNumber = 2;
  ::google::protobuf::int32 colormid() const;
  void set_colormid(::google::protobuf::int32 value);

  // double voltLow = 4;
  void clear_voltlow();
  static const int kVoltLowFieldNumber = 4;
  double voltlow() const;
  void set_voltlow(double value);

  // double voltMid = 5;
  void clear_voltmid();
  static const int kVoltMidFieldNumber = 5;
  double voltmid() const;
  void set_voltmid(double value);

  // double voltHigh = 6;
  void clear_volthigh();
  static const int kVoltHighFieldNumber = 6;
  double volthigh() const;
  void set_volthigh(double value);

  // int32 colorHigh = 3;
  void clear_colorhigh();
  static const int kColorHighFieldNumber = 3;
  ::google::protobuf::int32 colorhigh() const;
  void set_colorhigh(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Evrika.ProgSettings.BatColor)
 private:

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::int32 colorlow_;
  ::google::protobuf::int32 colormid_;
  double voltlow_;
  double voltmid_;
  double volthigh_;
  ::google::protobuf::int32 colorhigh_;
  mutable int _cached_size_;
  friend struct  protobuf_SaveSettings_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class ProgSettings_SignalLvlColor : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:Evrika.ProgSettings.SignalLvlColor) */ {
 public:
  ProgSettings_SignalLvlColor();
  virtual ~ProgSettings_SignalLvlColor();

  ProgSettings_SignalLvlColor(const ProgSettings_SignalLvlColor& from);

  inline ProgSettings_SignalLvlColor& operator=(const ProgSettings_SignalLvlColor& from) {
    CopyFrom(from);
    return *this;
  }

  static const ProgSettings_SignalLvlColor& default_instance();

  static inline const ProgSettings_SignalLvlColor* internal_default_instance() {
    return reinterpret_cast<const ProgSettings_SignalLvlColor*>(
               &_ProgSettings_SignalLvlColor_default_instance_);
  }

  void Swap(ProgSettings_SignalLvlColor* other);

  // implements Message ----------------------------------------------

  inline ProgSettings_SignalLvlColor* New() const PROTOBUF_FINAL { return New(NULL); }

  ProgSettings_SignalLvlColor* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    PROTOBUF_FINAL;
  void CopyFrom(const ProgSettings_SignalLvlColor& from);
  void MergeFrom(const ProgSettings_SignalLvlColor& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  void DiscardUnknownFields();
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(ProgSettings_SignalLvlColor* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::std::string GetTypeName() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // int32 colorLow = 1;
  void clear_colorlow();
  static const int kColorLowFieldNumber = 1;
  ::google::protobuf::int32 colorlow() const;
  void set_colorlow(::google::protobuf::int32 value);

  // int32 colorMid = 2;
  void clear_colormid();
  static const int kColorMidFieldNumber = 2;
  ::google::protobuf::int32 colormid() const;
  void set_colormid(::google::protobuf::int32 value);

  // int32 colorHigh = 3;
  void clear_colorhigh();
  static const int kColorHighFieldNumber = 3;
  ::google::protobuf::int32 colorhigh() const;
  void set_colorhigh(::google::protobuf::int32 value);

  // int32 lvlLow = 4;
  void clear_lvllow();
  static const int kLvlLowFieldNumber = 4;
  ::google::protobuf::int32 lvllow() const;
  void set_lvllow(::google::protobuf::int32 value);

  // int32 lvlMid = 5;
  void clear_lvlmid();
  static const int kLvlMidFieldNumber = 5;
  ::google::protobuf::int32 lvlmid() const;
  void set_lvlmid(::google::protobuf::int32 value);

  // int32 lvlHigh = 6;
  void clear_lvlhigh();
  static const int kLvlHighFieldNumber = 6;
  ::google::protobuf::int32 lvlhigh() const;
  void set_lvlhigh(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:Evrika.ProgSettings.SignalLvlColor)
 private:

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::int32 colorlow_;
  ::google::protobuf::int32 colormid_;
  ::google::protobuf::int32 colorhigh_;
  ::google::protobuf::int32 lvllow_;
  ::google::protobuf::int32 lvlmid_;
  ::google::protobuf::int32 lvlhigh_;
  mutable int _cached_size_;
  friend struct  protobuf_SaveSettings_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class ProgSettings : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:Evrika.ProgSettings) */ {
 public:
  ProgSettings();
  virtual ~ProgSettings();

  ProgSettings(const ProgSettings& from);

  inline ProgSettings& operator=(const ProgSettings& from) {
    CopyFrom(from);
    return *this;
  }

  static const ProgSettings& default_instance();

  static inline const ProgSettings* internal_default_instance() {
    return reinterpret_cast<const ProgSettings*>(
               &_ProgSettings_default_instance_);
  }

  void Swap(ProgSettings* other);

  // implements Message ----------------------------------------------

  inline ProgSettings* New() const PROTOBUF_FINAL { return New(NULL); }

  ProgSettings* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    PROTOBUF_FINAL;
  void CopyFrom(const ProgSettings& from);
  void MergeFrom(const ProgSettings& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  void DiscardUnknownFields();
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(ProgSettings* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::std::string GetTypeName() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  typedef ProgSettings_BatColor BatColor;
  typedef ProgSettings_SignalLvlColor SignalLvlColor;

  // accessors -------------------------------------------------------

  // string MapPath = 4;
  void clear_mappath();
  static const int kMapPathFieldNumber = 4;
  const ::std::string& mappath() const;
  void set_mappath(const ::std::string& value);
  #if LANG_CXX11
  void set_mappath(::std::string&& value);
  #endif
  void set_mappath(const char* value);
  void set_mappath(const char* value, size_t size);
  ::std::string* mutable_mappath();
  ::std::string* release_mappath();
  void set_allocated_mappath(::std::string* mappath);

  // .Evrika.ProgSettings.BatColor btclr = 1;
  bool has_btclr() const;
  void clear_btclr();
  static const int kBtclrFieldNumber = 1;
  const ::Evrika::ProgSettings_BatColor& btclr() const;
  ::Evrika::ProgSettings_BatColor* mutable_btclr();
  ::Evrika::ProgSettings_BatColor* release_btclr();
  void set_allocated_btclr(::Evrika::ProgSettings_BatColor* btclr);

  // .Evrika.ProgSettings.SignalLvlColor sgnllvlclr = 2;
  bool has_sgnllvlclr() const;
  void clear_sgnllvlclr();
  static const int kSgnllvlclrFieldNumber = 2;
  const ::Evrika::ProgSettings_SignalLvlColor& sgnllvlclr() const;
  ::Evrika::ProgSettings_SignalLvlColor* mutable_sgnllvlclr();
  ::Evrika::ProgSettings_SignalLvlColor* release_sgnllvlclr();
  void set_allocated_sgnllvlclr(::Evrika::ProgSettings_SignalLvlColor* sgnllvlclr);

  // uint32 MapProvider = 3;
  void clear_mapprovider();
  static const int kMapProviderFieldNumber = 3;
  ::google::protobuf::uint32 mapprovider() const;
  void set_mapprovider(::google::protobuf::uint32 value);

  // @@protoc_insertion_point(class_scope:Evrika.ProgSettings)
 private:

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr mappath_;
  ::Evrika::ProgSettings_BatColor* btclr_;
  ::Evrika::ProgSettings_SignalLvlColor* sgnllvlclr_;
  ::google::protobuf::uint32 mapprovider_;
  mutable int _cached_size_;
  friend struct  protobuf_SaveSettings_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class SettingPack : public ::google::protobuf::MessageLite /* @@protoc_insertion_point(class_definition:Evrika.SettingPack) */ {
 public:
  SettingPack();
  virtual ~SettingPack();

  SettingPack(const SettingPack& from);

  inline SettingPack& operator=(const SettingPack& from) {
    CopyFrom(from);
    return *this;
  }

  static const SettingPack& default_instance();

  static inline const SettingPack* internal_default_instance() {
    return reinterpret_cast<const SettingPack*>(
               &_SettingPack_default_instance_);
  }

  void Swap(SettingPack* other);

  // implements Message ----------------------------------------------

  inline SettingPack* New() const PROTOBUF_FINAL { return New(NULL); }

  SettingPack* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CheckTypeAndMergeFrom(const ::google::protobuf::MessageLite& from)
    PROTOBUF_FINAL;
  void CopyFrom(const SettingPack& from);
  void MergeFrom(const SettingPack& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  void DiscardUnknownFields();
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(SettingPack* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::std::string GetTypeName() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated .Evrika.ProgSettings prgstngs = 1;
  int prgstngs_size() const;
  void clear_prgstngs();
  static const int kPrgstngsFieldNumber = 1;
  const ::Evrika::ProgSettings& prgstngs(int index) const;
  ::Evrika::ProgSettings* mutable_prgstngs(int index);
  ::Evrika::ProgSettings* add_prgstngs();
  ::google::protobuf::RepeatedPtrField< ::Evrika::ProgSettings >*
      mutable_prgstngs();
  const ::google::protobuf::RepeatedPtrField< ::Evrika::ProgSettings >&
      prgstngs() const;

  // @@protoc_insertion_point(class_scope:Evrika.SettingPack)
 private:

  ::google::protobuf::internal::InternalMetadataWithArenaLite _internal_metadata_;
  ::google::protobuf::RepeatedPtrField< ::Evrika::ProgSettings > prgstngs_;
  mutable int _cached_size_;
  friend struct  protobuf_SaveSettings_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// ProgSettings_BatColor

// int32 colorLow = 1;
inline void ProgSettings_BatColor::clear_colorlow() {
  colorlow_ = 0;
}
inline ::google::protobuf::int32 ProgSettings_BatColor::colorlow() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.BatColor.colorLow)
  return colorlow_;
}
inline void ProgSettings_BatColor::set_colorlow(::google::protobuf::int32 value) {
  
  colorlow_ = value;
  // @@protoc_insertion_point(field_set:Evrika.ProgSettings.BatColor.colorLow)
}

// int32 colorMid = 2;
inline void ProgSettings_BatColor::clear_colormid() {
  colormid_ = 0;
}
inline ::google::protobuf::int32 ProgSettings_BatColor::colormid() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.BatColor.colorMid)
  return colormid_;
}
inline void ProgSettings_BatColor::set_colormid(::google::protobuf::int32 value) {
  
  colormid_ = value;
  // @@protoc_insertion_point(field_set:Evrika.ProgSettings.BatColor.colorMid)
}

// int32 colorHigh = 3;
inline void ProgSettings_BatColor::clear_colorhigh() {
  colorhigh_ = 0;
}
inline ::google::protobuf::int32 ProgSettings_BatColor::colorhigh() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.BatColor.colorHigh)
  return colorhigh_;
}
inline void ProgSettings_BatColor::set_colorhigh(::google::protobuf::int32 value) {
  
  colorhigh_ = value;
  // @@protoc_insertion_point(field_set:Evrika.ProgSettings.BatColor.colorHigh)
}

// double voltLow = 4;
inline void ProgSettings_BatColor::clear_voltlow() {
  voltlow_ = 0;
}
inline double ProgSettings_BatColor::voltlow() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.BatColor.voltLow)
  return voltlow_;
}
inline void ProgSettings_BatColor::set_voltlow(double value) {
  
  voltlow_ = value;
  // @@protoc_insertion_point(field_set:Evrika.ProgSettings.BatColor.voltLow)
}

// double voltMid = 5;
inline void ProgSettings_BatColor::clear_voltmid() {
  voltmid_ = 0;
}
inline double ProgSettings_BatColor::voltmid() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.BatColor.voltMid)
  return voltmid_;
}
inline void ProgSettings_BatColor::set_voltmid(double value) {
  
  voltmid_ = value;
  // @@protoc_insertion_point(field_set:Evrika.ProgSettings.BatColor.voltMid)
}

// double voltHigh = 6;
inline void ProgSettings_BatColor::clear_volthigh() {
  volthigh_ = 0;
}
inline double ProgSettings_BatColor::volthigh() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.BatColor.voltHigh)
  return volthigh_;
}
inline void ProgSettings_BatColor::set_volthigh(double value) {
  
  volthigh_ = value;
  // @@protoc_insertion_point(field_set:Evrika.ProgSettings.BatColor.voltHigh)
}

// -------------------------------------------------------------------

// ProgSettings_SignalLvlColor

// int32 colorLow = 1;
inline void ProgSettings_SignalLvlColor::clear_colorlow() {
  colorlow_ = 0;
}
inline ::google::protobuf::int32 ProgSettings_SignalLvlColor::colorlow() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.SignalLvlColor.colorLow)
  return colorlow_;
}
inline void ProgSettings_SignalLvlColor::set_colorlow(::google::protobuf::int32 value) {
  
  colorlow_ = value;
  // @@protoc_insertion_point(field_set:Evrika.ProgSettings.SignalLvlColor.colorLow)
}

// int32 colorMid = 2;
inline void ProgSettings_SignalLvlColor::clear_colormid() {
  colormid_ = 0;
}
inline ::google::protobuf::int32 ProgSettings_SignalLvlColor::colormid() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.SignalLvlColor.colorMid)
  return colormid_;
}
inline void ProgSettings_SignalLvlColor::set_colormid(::google::protobuf::int32 value) {
  
  colormid_ = value;
  // @@protoc_insertion_point(field_set:Evrika.ProgSettings.SignalLvlColor.colorMid)
}

// int32 colorHigh = 3;
inline void ProgSettings_SignalLvlColor::clear_colorhigh() {
  colorhigh_ = 0;
}
inline ::google::protobuf::int32 ProgSettings_SignalLvlColor::colorhigh() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.SignalLvlColor.colorHigh)
  return colorhigh_;
}
inline void ProgSettings_SignalLvlColor::set_colorhigh(::google::protobuf::int32 value) {
  
  colorhigh_ = value;
  // @@protoc_insertion_point(field_set:Evrika.ProgSettings.SignalLvlColor.colorHigh)
}

// int32 lvlLow = 4;
inline void ProgSettings_SignalLvlColor::clear_lvllow() {
  lvllow_ = 0;
}
inline ::google::protobuf::int32 ProgSettings_SignalLvlColor::lvllow() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.SignalLvlColor.lvlLow)
  return lvllow_;
}
inline void ProgSettings_SignalLvlColor::set_lvllow(::google::protobuf::int32 value) {
  
  lvllow_ = value;
  // @@protoc_insertion_point(field_set:Evrika.ProgSettings.SignalLvlColor.lvlLow)
}

// int32 lvlMid = 5;
inline void ProgSettings_SignalLvlColor::clear_lvlmid() {
  lvlmid_ = 0;
}
inline ::google::protobuf::int32 ProgSettings_SignalLvlColor::lvlmid() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.SignalLvlColor.lvlMid)
  return lvlmid_;
}
inline void ProgSettings_SignalLvlColor::set_lvlmid(::google::protobuf::int32 value) {
  
  lvlmid_ = value;
  // @@protoc_insertion_point(field_set:Evrika.ProgSettings.SignalLvlColor.lvlMid)
}

// int32 lvlHigh = 6;
inline void ProgSettings_SignalLvlColor::clear_lvlhigh() {
  lvlhigh_ = 0;
}
inline ::google::protobuf::int32 ProgSettings_SignalLvlColor::lvlhigh() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.SignalLvlColor.lvlHigh)
  return lvlhigh_;
}
inline void ProgSettings_SignalLvlColor::set_lvlhigh(::google::protobuf::int32 value) {
  
  lvlhigh_ = value;
  // @@protoc_insertion_point(field_set:Evrika.ProgSettings.SignalLvlColor.lvlHigh)
}

// -------------------------------------------------------------------

// ProgSettings

// .Evrika.ProgSettings.BatColor btclr = 1;
inline bool ProgSettings::has_btclr() const {
  return this != internal_default_instance() && btclr_ != NULL;
}
inline void ProgSettings::clear_btclr() {
  if (GetArenaNoVirtual() == NULL && btclr_ != NULL) delete btclr_;
  btclr_ = NULL;
}
inline const ::Evrika::ProgSettings_BatColor& ProgSettings::btclr() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.btclr)
  return btclr_ != NULL ? *btclr_
                         : *::Evrika::ProgSettings_BatColor::internal_default_instance();
}
inline ::Evrika::ProgSettings_BatColor* ProgSettings::mutable_btclr() {
  
  if (btclr_ == NULL) {
    btclr_ = new ::Evrika::ProgSettings_BatColor;
  }
  // @@protoc_insertion_point(field_mutable:Evrika.ProgSettings.btclr)
  return btclr_;
}
inline ::Evrika::ProgSettings_BatColor* ProgSettings::release_btclr() {
  // @@protoc_insertion_point(field_release:Evrika.ProgSettings.btclr)
  
  ::Evrika::ProgSettings_BatColor* temp = btclr_;
  btclr_ = NULL;
  return temp;
}
inline void ProgSettings::set_allocated_btclr(::Evrika::ProgSettings_BatColor* btclr) {
  delete btclr_;
  btclr_ = btclr;
  if (btclr) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:Evrika.ProgSettings.btclr)
}

// .Evrika.ProgSettings.SignalLvlColor sgnllvlclr = 2;
inline bool ProgSettings::has_sgnllvlclr() const {
  return this != internal_default_instance() && sgnllvlclr_ != NULL;
}
inline void ProgSettings::clear_sgnllvlclr() {
  if (GetArenaNoVirtual() == NULL && sgnllvlclr_ != NULL) delete sgnllvlclr_;
  sgnllvlclr_ = NULL;
}
inline const ::Evrika::ProgSettings_SignalLvlColor& ProgSettings::sgnllvlclr() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.sgnllvlclr)
  return sgnllvlclr_ != NULL ? *sgnllvlclr_
                         : *::Evrika::ProgSettings_SignalLvlColor::internal_default_instance();
}
inline ::Evrika::ProgSettings_SignalLvlColor* ProgSettings::mutable_sgnllvlclr() {
  
  if (sgnllvlclr_ == NULL) {
    sgnllvlclr_ = new ::Evrika::ProgSettings_SignalLvlColor;
  }
  // @@protoc_insertion_point(field_mutable:Evrika.ProgSettings.sgnllvlclr)
  return sgnllvlclr_;
}
inline ::Evrika::ProgSettings_SignalLvlColor* ProgSettings::release_sgnllvlclr() {
  // @@protoc_insertion_point(field_release:Evrika.ProgSettings.sgnllvlclr)
  
  ::Evrika::ProgSettings_SignalLvlColor* temp = sgnllvlclr_;
  sgnllvlclr_ = NULL;
  return temp;
}
inline void ProgSettings::set_allocated_sgnllvlclr(::Evrika::ProgSettings_SignalLvlColor* sgnllvlclr) {
  delete sgnllvlclr_;
  sgnllvlclr_ = sgnllvlclr;
  if (sgnllvlclr) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:Evrika.ProgSettings.sgnllvlclr)
}

// uint32 MapProvider = 3;
inline void ProgSettings::clear_mapprovider() {
  mapprovider_ = 0u;
}
inline ::google::protobuf::uint32 ProgSettings::mapprovider() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.MapProvider)
  return mapprovider_;
}
inline void ProgSettings::set_mapprovider(::google::protobuf::uint32 value) {
  
  mapprovider_ = value;
  // @@protoc_insertion_point(field_set:Evrika.ProgSettings.MapProvider)
}

// string MapPath = 4;
inline void ProgSettings::clear_mappath() {
  mappath_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& ProgSettings::mappath() const {
  // @@protoc_insertion_point(field_get:Evrika.ProgSettings.MapPath)
  return mappath_.GetNoArena();
}
inline void ProgSettings::set_mappath(const ::std::string& value) {
  
  mappath_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:Evrika.ProgSettings.MapPath)
}
#if LANG_CXX11
inline void ProgSettings::set_mappath(::std::string&& value) {
  
  mappath_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:Evrika.ProgSettings.MapPath)
}
#endif
inline void ProgSettings::set_mappath(const char* value) {
  
  mappath_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:Evrika.ProgSettings.MapPath)
}
inline void ProgSettings::set_mappath(const char* value, size_t size) {
  
  mappath_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:Evrika.ProgSettings.MapPath)
}
inline ::std::string* ProgSettings::mutable_mappath() {
  
  // @@protoc_insertion_point(field_mutable:Evrika.ProgSettings.MapPath)
  return mappath_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* ProgSettings::release_mappath() {
  // @@protoc_insertion_point(field_release:Evrika.ProgSettings.MapPath)
  
  return mappath_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void ProgSettings::set_allocated_mappath(::std::string* mappath) {
  if (mappath != NULL) {
    
  } else {
    
  }
  mappath_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), mappath);
  // @@protoc_insertion_point(field_set_allocated:Evrika.ProgSettings.MapPath)
}

// -------------------------------------------------------------------

// SettingPack

// repeated .Evrika.ProgSettings prgstngs = 1;
inline int SettingPack::prgstngs_size() const {
  return prgstngs_.size();
}
inline void SettingPack::clear_prgstngs() {
  prgstngs_.Clear();
}
inline const ::Evrika::ProgSettings& SettingPack::prgstngs(int index) const {
  // @@protoc_insertion_point(field_get:Evrika.SettingPack.prgstngs)
  return prgstngs_.Get(index);
}
inline ::Evrika::ProgSettings* SettingPack::mutable_prgstngs(int index) {
  // @@protoc_insertion_point(field_mutable:Evrika.SettingPack.prgstngs)
  return prgstngs_.Mutable(index);
}
inline ::Evrika::ProgSettings* SettingPack::add_prgstngs() {
  // @@protoc_insertion_point(field_add:Evrika.SettingPack.prgstngs)
  return prgstngs_.Add();
}
inline ::google::protobuf::RepeatedPtrField< ::Evrika::ProgSettings >*
SettingPack::mutable_prgstngs() {
  // @@protoc_insertion_point(field_mutable_list:Evrika.SettingPack.prgstngs)
  return &prgstngs_;
}
inline const ::google::protobuf::RepeatedPtrField< ::Evrika::ProgSettings >&
SettingPack::prgstngs() const {
  // @@protoc_insertion_point(field_list:Evrika.SettingPack.prgstngs)
  return prgstngs_;
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------

// -------------------------------------------------------------------

// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace Evrika

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_SaveSettings_2eproto__INCLUDED
