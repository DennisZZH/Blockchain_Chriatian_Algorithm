// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Msg.proto

#include "Msg.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
extern PROTOBUF_INTERNAL_EXPORT_Msg_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_transaction_t_Msg_2eproto;
class transaction_tDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<transaction_t> _instance;
} _transaction_t_default_instance_;
class message_tDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<message_t> _instance;
} _message_t_default_instance_;
class time_tDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<time_t> _instance;
} _time_t_default_instance_;
static void InitDefaultsscc_info_message_t_Msg_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_message_t_default_instance_;
    new (ptr) ::message_t();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::message_t::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_message_t_Msg_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, 0, InitDefaultsscc_info_message_t_Msg_2eproto}, {
      &scc_info_transaction_t_Msg_2eproto.base,}};

static void InitDefaultsscc_info_time_t_Msg_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_time_t_default_instance_;
    new (ptr) ::time_t();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::time_t::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_time_t_Msg_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_time_t_Msg_2eproto}, {}};

static void InitDefaultsscc_info_transaction_t_Msg_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_transaction_t_default_instance_;
    new (ptr) ::transaction_t();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::transaction_t::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_transaction_t_Msg_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_transaction_t_Msg_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_Msg_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_Msg_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_Msg_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_Msg_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::transaction_t, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::transaction_t, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::transaction_t, sender_id_),
  PROTOBUF_FIELD_OFFSET(::transaction_t, receiver_id_),
  PROTOBUF_FIELD_OFFSET(::transaction_t, amount_),
  0,
  1,
  2,
  PROTOBUF_FIELD_OFFSET(::message_t, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::message_t, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::message_t, timestamp_),
  PROTOBUF_FIELD_OFFSET(::message_t, client_id_),
  PROTOBUF_FIELD_OFFSET(::message_t, transaction_),
  1,
  2,
  0,
  PROTOBUF_FIELD_OFFSET(::time_t, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::time_t, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::time_t, seconds_),
  PROTOBUF_FIELD_OFFSET(::time_t, nanos_),
  0,
  1,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 8, sizeof(::transaction_t)},
  { 11, 19, sizeof(::message_t)},
  { 22, 29, sizeof(::time_t)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_transaction_t_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_message_t_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_time_t_default_instance_),
};

const char descriptor_table_protodef_Msg_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\tMsg.proto\"G\n\rtransaction_t\022\021\n\tsender_i"
  "d\030\001 \002(\005\022\023\n\013receiver_id\030\002 \002(\005\022\016\n\006amount\030\003"
  " \002(\002\"V\n\tmessage_t\022\021\n\ttimestamp\030\001 \002(\005\022\021\n\t"
  "client_id\030\002 \002(\005\022#\n\013transaction\030\003 \002(\0132\016.t"
  "ransaction_t\"(\n\006time_t\022\017\n\007seconds\030\001 \002(\003\022"
  "\r\n\005nanos\030\002 \002(\005"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_Msg_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_Msg_2eproto_sccs[3] = {
  &scc_info_message_t_Msg_2eproto.base,
  &scc_info_time_t_Msg_2eproto.base,
  &scc_info_transaction_t_Msg_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_Msg_2eproto_once;
static bool descriptor_table_Msg_2eproto_initialized = false;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_Msg_2eproto = {
  &descriptor_table_Msg_2eproto_initialized, descriptor_table_protodef_Msg_2eproto, "Msg.proto", 214,
  &descriptor_table_Msg_2eproto_once, descriptor_table_Msg_2eproto_sccs, descriptor_table_Msg_2eproto_deps, 3, 0,
  schemas, file_default_instances, TableStruct_Msg_2eproto::offsets,
  file_level_metadata_Msg_2eproto, 3, file_level_enum_descriptors_Msg_2eproto, file_level_service_descriptors_Msg_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_Msg_2eproto = (  ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_Msg_2eproto), true);

// ===================================================================

void transaction_t::InitAsDefaultInstance() {
}
class transaction_t::_Internal {
 public:
  using HasBits = decltype(std::declval<transaction_t>()._has_bits_);
  static void set_has_sender_id(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_receiver_id(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_amount(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
};

transaction_t::transaction_t()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:transaction_t)
}
transaction_t::transaction_t(const transaction_t& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&sender_id_, &from.sender_id_,
    static_cast<size_t>(reinterpret_cast<char*>(&amount_) -
    reinterpret_cast<char*>(&sender_id_)) + sizeof(amount_));
  // @@protoc_insertion_point(copy_constructor:transaction_t)
}

void transaction_t::SharedCtor() {
  ::memset(&sender_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&amount_) -
      reinterpret_cast<char*>(&sender_id_)) + sizeof(amount_));
}

transaction_t::~transaction_t() {
  // @@protoc_insertion_point(destructor:transaction_t)
  SharedDtor();
}

void transaction_t::SharedDtor() {
}

void transaction_t::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const transaction_t& transaction_t::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_transaction_t_Msg_2eproto.base);
  return *internal_default_instance();
}


void transaction_t::Clear() {
// @@protoc_insertion_point(message_clear_start:transaction_t)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    ::memset(&sender_id_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&amount_) -
        reinterpret_cast<char*>(&sender_id_)) + sizeof(amount_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

const char* transaction_t::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // required int32 sender_id = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _Internal::set_has_sender_id(&has_bits);
          sender_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // required int32 receiver_id = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_receiver_id(&has_bits);
          receiver_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // required float amount = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 29)) {
          _Internal::set_has_amount(&has_bits);
          amount_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* transaction_t::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:transaction_t)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required int32 sender_id = 1;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_sender_id(), target);
  }

  // required int32 receiver_id = 2;
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_receiver_id(), target);
  }

  // required float amount = 3;
  if (cached_has_bits & 0x00000004u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFloatToArray(3, this->_internal_amount(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:transaction_t)
  return target;
}

size_t transaction_t::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:transaction_t)
  size_t total_size = 0;

  if (_internal_has_sender_id()) {
    // required int32 sender_id = 1;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_sender_id());
  }

  if (_internal_has_receiver_id()) {
    // required int32 receiver_id = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_receiver_id());
  }

  if (_internal_has_amount()) {
    // required float amount = 3;
    total_size += 1 + 4;
  }

  return total_size;
}
size_t transaction_t::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:transaction_t)
  size_t total_size = 0;

  if (((_has_bits_[0] & 0x00000007) ^ 0x00000007) == 0) {  // All required fields are present.
    // required int32 sender_id = 1;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_sender_id());

    // required int32 receiver_id = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_receiver_id());

    // required float amount = 3;
    total_size += 1 + 4;

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void transaction_t::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:transaction_t)
  GOOGLE_DCHECK_NE(&from, this);
  const transaction_t* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<transaction_t>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:transaction_t)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:transaction_t)
    MergeFrom(*source);
  }
}

void transaction_t::MergeFrom(const transaction_t& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:transaction_t)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    if (cached_has_bits & 0x00000001u) {
      sender_id_ = from.sender_id_;
    }
    if (cached_has_bits & 0x00000002u) {
      receiver_id_ = from.receiver_id_;
    }
    if (cached_has_bits & 0x00000004u) {
      amount_ = from.amount_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void transaction_t::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:transaction_t)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void transaction_t::CopyFrom(const transaction_t& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:transaction_t)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool transaction_t::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;
  return true;
}

void transaction_t::InternalSwap(transaction_t* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(sender_id_, other->sender_id_);
  swap(receiver_id_, other->receiver_id_);
  swap(amount_, other->amount_);
}

::PROTOBUF_NAMESPACE_ID::Metadata transaction_t::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void message_t::InitAsDefaultInstance() {
  ::_message_t_default_instance_._instance.get_mutable()->transaction_ = const_cast< ::transaction_t*>(
      ::transaction_t::internal_default_instance());
}
class message_t::_Internal {
 public:
  using HasBits = decltype(std::declval<message_t>()._has_bits_);
  static void set_has_timestamp(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static void set_has_client_id(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static const ::transaction_t& transaction(const message_t* msg);
  static void set_has_transaction(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

const ::transaction_t&
message_t::_Internal::transaction(const message_t* msg) {
  return *msg->transaction_;
}
message_t::message_t()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:message_t)
}
message_t::message_t(const message_t& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  if (from._internal_has_transaction()) {
    transaction_ = new ::transaction_t(*from.transaction_);
  } else {
    transaction_ = nullptr;
  }
  ::memcpy(&timestamp_, &from.timestamp_,
    static_cast<size_t>(reinterpret_cast<char*>(&client_id_) -
    reinterpret_cast<char*>(&timestamp_)) + sizeof(client_id_));
  // @@protoc_insertion_point(copy_constructor:message_t)
}

void message_t::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_message_t_Msg_2eproto.base);
  ::memset(&transaction_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&client_id_) -
      reinterpret_cast<char*>(&transaction_)) + sizeof(client_id_));
}

message_t::~message_t() {
  // @@protoc_insertion_point(destructor:message_t)
  SharedDtor();
}

void message_t::SharedDtor() {
  if (this != internal_default_instance()) delete transaction_;
}

void message_t::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const message_t& message_t::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_message_t_Msg_2eproto.base);
  return *internal_default_instance();
}


void message_t::Clear() {
// @@protoc_insertion_point(message_clear_start:message_t)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    GOOGLE_DCHECK(transaction_ != nullptr);
    transaction_->Clear();
  }
  if (cached_has_bits & 0x00000006u) {
    ::memset(&timestamp_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&client_id_) -
        reinterpret_cast<char*>(&timestamp_)) + sizeof(client_id_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

const char* message_t::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // required int32 timestamp = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _Internal::set_has_timestamp(&has_bits);
          timestamp_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // required int32 client_id = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_client_id(&has_bits);
          client_id_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // required .transaction_t transaction = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          ptr = ctx->ParseMessage(_internal_mutable_transaction(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* message_t::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:message_t)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required int32 timestamp = 1;
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_timestamp(), target);
  }

  // required int32 client_id = 2;
  if (cached_has_bits & 0x00000004u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_client_id(), target);
  }

  // required .transaction_t transaction = 3;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        3, _Internal::transaction(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:message_t)
  return target;
}

size_t message_t::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:message_t)
  size_t total_size = 0;

  if (_internal_has_transaction()) {
    // required .transaction_t transaction = 3;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *transaction_);
  }

  if (_internal_has_timestamp()) {
    // required int32 timestamp = 1;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_timestamp());
  }

  if (_internal_has_client_id()) {
    // required int32 client_id = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_client_id());
  }

  return total_size;
}
size_t message_t::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:message_t)
  size_t total_size = 0;

  if (((_has_bits_[0] & 0x00000007) ^ 0x00000007) == 0) {  // All required fields are present.
    // required .transaction_t transaction = 3;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *transaction_);

    // required int32 timestamp = 1;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_timestamp());

    // required int32 client_id = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_client_id());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void message_t::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:message_t)
  GOOGLE_DCHECK_NE(&from, this);
  const message_t* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<message_t>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:message_t)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:message_t)
    MergeFrom(*source);
  }
}

void message_t::MergeFrom(const message_t& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:message_t)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    if (cached_has_bits & 0x00000001u) {
      _internal_mutable_transaction()->::transaction_t::MergeFrom(from._internal_transaction());
    }
    if (cached_has_bits & 0x00000002u) {
      timestamp_ = from.timestamp_;
    }
    if (cached_has_bits & 0x00000004u) {
      client_id_ = from.client_id_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void message_t::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:message_t)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void message_t::CopyFrom(const message_t& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:message_t)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool message_t::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;
  if (_internal_has_transaction()) {
    if (!transaction_->IsInitialized()) return false;
  }
  return true;
}

void message_t::InternalSwap(message_t* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(transaction_, other->transaction_);
  swap(timestamp_, other->timestamp_);
  swap(client_id_, other->client_id_);
}

::PROTOBUF_NAMESPACE_ID::Metadata message_t::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void time_t::InitAsDefaultInstance() {
}
class time_t::_Internal {
 public:
  using HasBits = decltype(std::declval<time_t>()._has_bits_);
  static void set_has_seconds(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_nanos(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
};

time_t::time_t()
  : ::PROTOBUF_NAMESPACE_ID::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:time_t)
}
time_t::time_t(const time_t& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::memcpy(&seconds_, &from.seconds_,
    static_cast<size_t>(reinterpret_cast<char*>(&nanos_) -
    reinterpret_cast<char*>(&seconds_)) + sizeof(nanos_));
  // @@protoc_insertion_point(copy_constructor:time_t)
}

void time_t::SharedCtor() {
  ::memset(&seconds_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&nanos_) -
      reinterpret_cast<char*>(&seconds_)) + sizeof(nanos_));
}

time_t::~time_t() {
  // @@protoc_insertion_point(destructor:time_t)
  SharedDtor();
}

void time_t::SharedDtor() {
}

void time_t::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const time_t& time_t::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_time_t_Msg_2eproto.base);
  return *internal_default_instance();
}


void time_t::Clear() {
// @@protoc_insertion_point(message_clear_start:time_t)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    ::memset(&seconds_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&nanos_) -
        reinterpret_cast<char*>(&seconds_)) + sizeof(nanos_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

const char* time_t::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // required int64 seconds = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          _Internal::set_has_seconds(&has_bits);
          seconds_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // required int32 nanos = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_nanos(&has_bits);
          nanos_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag, &_internal_metadata_, ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* time_t::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:time_t)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required int64 seconds = 1;
  if (cached_has_bits & 0x00000001u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt64ToArray(1, this->_internal_seconds(), target);
  }

  // required int32 nanos = 2;
  if (cached_has_bits & 0x00000002u) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_nanos(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:time_t)
  return target;
}

size_t time_t::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:time_t)
  size_t total_size = 0;

  if (_internal_has_seconds()) {
    // required int64 seconds = 1;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
        this->_internal_seconds());
  }

  if (_internal_has_nanos()) {
    // required int32 nanos = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_nanos());
  }

  return total_size;
}
size_t time_t::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:time_t)
  size_t total_size = 0;

  if (((_has_bits_[0] & 0x00000003) ^ 0x00000003) == 0) {  // All required fields are present.
    // required int64 seconds = 1;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int64Size(
        this->_internal_seconds());

    // required int32 nanos = 2;
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_nanos());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void time_t::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:time_t)
  GOOGLE_DCHECK_NE(&from, this);
  const time_t* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<time_t>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:time_t)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:time_t)
    MergeFrom(*source);
  }
}

void time_t::MergeFrom(const time_t& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:time_t)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      seconds_ = from.seconds_;
    }
    if (cached_has_bits & 0x00000002u) {
      nanos_ = from.nanos_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void time_t::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:time_t)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void time_t::CopyFrom(const time_t& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:time_t)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool time_t::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000003) != 0x00000003) return false;
  return true;
}

void time_t::InternalSwap(time_t* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  swap(seconds_, other->seconds_);
  swap(nanos_, other->nanos_);
}

::PROTOBUF_NAMESPACE_ID::Metadata time_t::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::transaction_t* Arena::CreateMaybeMessage< ::transaction_t >(Arena* arena) {
  return Arena::CreateInternal< ::transaction_t >(arena);
}
template<> PROTOBUF_NOINLINE ::message_t* Arena::CreateMaybeMessage< ::message_t >(Arena* arena) {
  return Arena::CreateInternal< ::message_t >(arena);
}
template<> PROTOBUF_NOINLINE ::time_t* Arena::CreateMaybeMessage< ::time_t >(Arena* arena) {
  return Arena::CreateInternal< ::time_t >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>