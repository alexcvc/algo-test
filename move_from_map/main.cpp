#include <fmt/format.h>
#include <algorithm>
#include <climits>
#include <iostream>
#include <string>

#define MMSd_noHandlerErrors                    0x00000000UL
#define MMSd_emitOverflow                       0x00000001UL
#define MMSd_fetchLengthError                   0x00000002UL
#define MMSd_data_object_invalidated            0x00000004UL
#define MMSd_data_hardware_fault                0x00000008UL
#define MMSd_data_temporarily_unavailable       0x00000010UL
#define MMSd_data_object_access_denied          0x00000020UL
#define MMSd_data_object_undefined              0x00000040UL
#define MMSd_data_invalid_address               0x00000080UL
#define MMSd_data_type_unsupported              0x00000100UL
#define MMSd_data_type_inconsistent             0x00000200UL
#define MMSd_data_object_attribute_inconsistent 0x00000400UL
#define MMSd_data_object_access_unsupported     0x00000800UL
#define MMSd_data_object_non_existent           0x00001000UL
#define MMSd_queueOverrun                       0x00002000UL
#define MMSd_null_descriptor                    0x00004000UL
#define MMSd_IOargs                             0x00008000UL
#define MMSd_neg_svc_error                      0x00010000UL
#define MMSd_data_object_value_invalid          0x00020000UL
#define MMSd_search_error                       0x00040000UL
#define MMSd_pdu_error                          0x00080000UL
#define MMSd_file_other                         0x00100000UL
#define MMSd_file_file_busy                     0x00200000UL
#define MMSd_file_name_syntax_error             0x00400000UL
#define MMSd_file_content_invalid               0x00800000UL
#define MMSd_file_file_access_denied            0x01000000UL
#define MMSd_file_file_non_existent             0x02000000UL
#define MMSd_file_duplicate_filename            0x04000000UL
#define MMSd_file_insufficient_space            0x08000000UL
#define MMSd_file_position_invalid              0x10000000UL
#define MMSd_authentication_failure             0x20000000UL
#define MMSd_authentication_mech_nr             0x40000000UL
#define MMSd_uninitiatedMessage                 0x80000000UL
#define MMSd_anyError                           0xFFFFFFFFUL
#define MMSd_GLOBAL_ERROR     \
  ( MMSd_emitOverflow | MMSd_fetchLengthError | MMSd_queueOverrun \
    | MMSd_null_descriptor | MMSd_IOargs | MMSd_neg_svc_error \
    | MMSd_search_error | MMSd_pdu_error \
    | MMSd_file_other \
    | MMSd_file_file_busy \
    | MMSd_file_name_syntax_error \
    | MMSd_file_content_invalid \
    | MMSd_file_file_access_denied \
    | MMSd_file_file_non_existent \
    | MMSd_file_duplicate_filename \
    | MMSd_file_insufficient_space \
    | MMSd_file_position_invalid \
    | MMSd_authentication_failure \
    | MMSd_authentication_mech_nr )

std::string&& to_string_mms_error(int error) {
  static std::unordered_map<int, std::string> errorMap{
     {MMSd_noHandlerErrors, "no errors"},
     {MMSd_emitOverflow, "pdu overflow"},
     {MMSd_fetchLengthError, "encoding error"},
     {MMSd_data_object_invalidated, "object invalidated"},
     {MMSd_data_hardware_fault, "hardware fault"},
     {MMSd_data_temporarily_unavailable, "temporarily unavailable"},
     {MMSd_data_object_access_denied, "object access_denied"},
     {MMSd_data_object_undefined, "object undefined"},
     {MMSd_data_invalid_address, "invalid address"},
     {MMSd_data_type_unsupported, "type unsupported"},
     {MMSd_data_type_inconsistent, "type inconsistent"},
     {MMSd_data_object_attribute_inconsistent, "object attribute inconsistent"},
     {MMSd_data_object_access_unsupported, "object access unsupported"},
     {MMSd_data_object_non_existent, "object non existent"},
     {MMSd_queueOverrun, "queue overrun"},
     {MMSd_null_descriptor, "null descriptor"},
     {MMSd_IOargs, "internal error"},
     {MMSd_neg_svc_error, "negotiated service error"},
     {MMSd_data_object_value_invalid, "object value invalid"},
     {MMSd_search_error, "search error"},
     {MMSd_pdu_error, "pdu error"},
     {MMSd_file_other, "file other"},
     {MMSd_file_file_busy, "file busy"},
     {MMSd_file_name_syntax_error, "file name syntax error"},
     {MMSd_file_content_invalid, "file content invalid"},
     {MMSd_file_file_access_denied, "file access denied"},
     {MMSd_file_file_non_existent, "file non existent"},
     {MMSd_file_duplicate_filename, "file duplicate filename"},
     {MMSd_file_insufficient_space, "file insufficient space"},
     {MMSd_file_position_invalid, "file position invalid"},
     {MMSd_authentication_failure, "authentication failure"},
     {MMSd_authentication_mech_nr, "authentication mech nr"},
     {MMSd_uninitiatedMessage, "no association"}
  };
  static std::string err_msg;
  if (auto it = errorMap.find(error); it != errorMap.end()) {
    return std::move(it->second);
  } else {
    err_msg = fmt::format("unknown error={:#08x}", (uint)error);
    return std::move(err_msg);
  }
}


int main() {

  std::cout << to_string_mms_error(MMSd_noHandlerErrors                   ) << std::endl;
  std::cout << to_string_mms_error(MMSd_emitOverflow                      ) << std::endl;
  std::cout << to_string_mms_error(MMSd_fetchLengthError                  ) << std::endl;
  std::cout << to_string_mms_error(MMSd_data_object_invalidated           ) << std::endl;
  std::cout << to_string_mms_error(MMSd_data_hardware_fault               ) << std::endl;
  std::cout << to_string_mms_error(MMSd_data_temporarily_unavailable      ) << std::endl;
  std::cout << to_string_mms_error(MMSd_data_object_access_denied         ) << std::endl;
  std::cout << to_string_mms_error(MMSd_data_object_undefined             ) << std::endl;
  std::cout << to_string_mms_error(MMSd_data_invalid_address              ) << std::endl;
  std::cout << to_string_mms_error(MMSd_data_type_unsupported             ) << std::endl;
  std::cout << to_string_mms_error(MMSd_data_type_inconsistent            ) << std::endl;
  std::cout << to_string_mms_error(MMSd_data_object_attribute_inconsistent) << std::endl;
  std::cout << to_string_mms_error(MMSd_data_object_access_unsupported    ) << std::endl;
  std::cout << to_string_mms_error(MMSd_data_object_non_existent          ) << std::endl;
  std::cout << to_string_mms_error(MMSd_queueOverrun                      ) << std::endl;
  std::cout << to_string_mms_error(MMSd_null_descriptor                   ) << std::endl;
  std::cout << to_string_mms_error(MMSd_IOargs                            ) << std::endl;
  std::cout << to_string_mms_error(MMSd_neg_svc_error                     ) << std::endl;
  std::cout << to_string_mms_error(MMSd_data_object_value_invalid         ) << std::endl;
  std::cout << to_string_mms_error(MMSd_search_error                      ) << std::endl;
  std::cout << to_string_mms_error(MMSd_pdu_error                         ) << std::endl;
  std::cout << to_string_mms_error(MMSd_file_other                        ) << std::endl;
  std::cout << to_string_mms_error(MMSd_file_file_busy                    ) << std::endl;
  std::cout << to_string_mms_error(MMSd_file_name_syntax_error            ) << std::endl;
  std::cout << to_string_mms_error(MMSd_file_content_invalid              ) << std::endl;
  std::cout << to_string_mms_error(MMSd_file_file_access_denied           ) << std::endl;
  std::cout << to_string_mms_error(MMSd_file_file_non_existent            ) << std::endl;
  std::cout << to_string_mms_error(MMSd_file_duplicate_filename           ) << std::endl;
  std::cout << to_string_mms_error(MMSd_file_insufficient_space           ) << std::endl;
  std::cout << to_string_mms_error(MMSd_file_position_invalid             ) << std::endl;
  std::cout << to_string_mms_error(MMSd_authentication_failure            ) << std::endl;
  std::cout << to_string_mms_error(MMSd_authentication_mech_nr            ) << std::endl;
  std::cout << to_string_mms_error(MMSd_uninitiatedMessage                ) << std::endl;
  std::cout << to_string_mms_error(MMSd_anyError                          ) << std::endl;
  std::cout << to_string_mms_error(MMSd_GLOBAL_ERROR                      ) << std::endl;


  return 0;
}
