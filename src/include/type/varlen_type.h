//===----------------------------------------------------------------------===//
//
//                         Peloton
//
// varlen_value.h
//
// Identification: src/backend/type/varlen_value.h
//
// Copyright (c) 2015-16, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include "type/value.h"

namespace peloton {
namespace type {

// A varlen value is an abstract class representing all objects that have
// variable length.
class VarlenType : public Type {
 public:
  VarlenType(TypeId type);
  ~VarlenType();
  
  // Access the raw variable length data
  const char *GetData(const Value& val) const;

  // Access the raw varlen data stored from the tuple storage
  char *GetData(char *storage) override;

  // Get the length of the variable length data
  uint32_t GetLength(const Value& val) const;

  // Comparison functions
  Value CompareEquals(const Value& left, const Value &right) const override;
  Value CompareNotEquals(const Value& left, const Value &right) const override;
  Value CompareLessThan(const Value& left, const Value &right) const override;
  Value CompareLessThanEquals(const Value& left, const Value &right) const override;
  Value CompareGreaterThan(const Value& left, const Value &right) const override;
  Value CompareGreaterThanEquals(const Value& left, const Value &right) const override;

  Value CastAs(const Value& val, const Type::TypeId type_id) const override;

  // Decimal types are always inlined
  bool IsInlined(const Value&) const override { return false; }

  // Debug
  std::string ToString(const Value& val) const override;

  // Compute a hash value
  size_t Hash(const Value& val) const override;
  void HashCombine(const Value& val, size_t &seed) const override;

  // Serialize this value into the given storage space
  void SerializeTo(const Value& val, SerializeOutput &out) const override;
  void SerializeTo(const Value& val, char *storage, bool inlined,
                   VarlenPool *pool) const override;

  // Deserialize a value of the given type from the given storage space.
  Value DeserializeFrom(const char *storage,
                                const bool inlined, VarlenPool *pool = nullptr) const override;
  Value DeserializeFrom(SerializeInput &in,
                                VarlenPool *pool = nullptr) const override;

  // Perform a shallow copy from a serialized varlen value to another serialized varlen value
  void DoShallowCopy(char *dest, char *src, bool inlined, VarlenPool *src_pool) const override;

  // Create a copy of this value
  Value Copy(const Value& val) const override;
};

}  // namespace type
}  // namespace peloton
