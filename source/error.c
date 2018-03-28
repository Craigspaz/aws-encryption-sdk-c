/*
 * Copyright 2018 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You may not use
 * this file except in compliance with the License. A copy of the License is
 * located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
 * implied. See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <aws/cryptosdk/error.h>

static const struct aws_error_info error_info[] = {
    AWS_DEFINE_ERROR_INFO(AWS_CRYPTOSDK_ERR_BAD_CIPHERTEXT, AWS_CRYPTOSDK_ERR_BAD_CIPHERTEXT, "Bad ciphertext", "cryptosdk")
};

static const struct aws_error_info_list error_info_list = {
    .error_list = error_info,
    .count = sizeof(error_info)/sizeof(error_info[0])
};

void aws_cryptosdk_err_init_strings() {
    aws_register_error_info(&error_info_list);
}