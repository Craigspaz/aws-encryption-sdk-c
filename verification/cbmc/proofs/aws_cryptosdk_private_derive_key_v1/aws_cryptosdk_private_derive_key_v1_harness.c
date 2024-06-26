/*
 * Copyright 2020 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include <aws/cryptosdk/cipher.h>
#include <aws/cryptosdk/private/cipher.h>
#include <aws/cryptosdk/private/hkdf.h>
#include <make_common_data_structures.h>
#include <utils.h>

int __CPROVER_file_local_cipher_c_aws_cryptosdk_private_derive_key_v1(
    const struct aws_cryptosdk_alg_properties *props,
    struct content_key *content_key,
    const struct data_key *data_key,
    const struct aws_byte_buf *message_id);

void aws_cryptosdk_private_derive_key_v1_harness() {
    struct aws_cryptosdk_alg_properties *props = ensure_alg_properties_attempt_allocation(MAX_STRING_LEN);
    struct content_key *content_key            = ensure_content_key_attempt_allocation();
    struct data_key *data_key                  = ensure_data_key_attempt_allocation();
    struct aws_byte_buf *message_id            = malloc(sizeof(*message_id));

    /* Assumptions */
    __CPROVER_assume(aws_cryptosdk_alg_properties_is_valid(props));

    __CPROVER_assume(aws_cryptosdk_content_key_is_valid(content_key));

    __CPROVER_assume(aws_cryptosdk_data_key_is_valid(data_key));

    __CPROVER_assume(IMPLIES(message_id != NULL, aws_byte_buf_is_bounded(message_id, MAX_BUFFER_SIZE)));
    ensure_byte_buf_has_allocated_buffer_member(message_id);
    __CPROVER_assume(aws_byte_buf_is_valid(message_id));

    /* Save current state of the data structure */
    struct aws_byte_buf *old_message_id = message_id;
    struct store_byte_from_buffer old_byte_from_message_id;
    save_byte_from_array(message_id->buffer, message_id->len, &old_byte_from_message_id);

    /* Operation under verification */
    int rv =
        __CPROVER_file_local_cipher_c_aws_cryptosdk_private_derive_key_v1(props, content_key, data_key, message_id);

    /* Postconditions */
    assert(aws_cryptosdk_alg_properties_is_valid(props));
    assert(aws_cryptosdk_content_key_is_valid(content_key));
    assert(aws_cryptosdk_data_key_is_valid(data_key));
    assert(aws_byte_buf_is_valid(message_id));
    assert_byte_buf_equivalence(message_id, old_message_id, &old_byte_from_message_id);
    if (rv == AWS_CRYPTOSDK_ERR_UNSUPPORTED_FORMAT) {
        assert(message_id->len != MSG_ID_LEN);
    } else if (rv == AWS_OP_SUCCESS && aws_cryptosdk_which_sha(props->alg_id) == AWS_CRYPTOSDK_NOSHA) {
        assert(key_contents_match(content_key, data_key, props->data_key_len));
    }
}
