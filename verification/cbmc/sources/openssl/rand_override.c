/*
 * Copyright 2019 Amazon.com, Inc. or its affiliates. All Rights Reserved.
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

#include <make_common_data_structures.h>
#include <openssl/rand.h>

/*
 * RAND_bytes() puts num cryptographically strong pseudo-random bytes into buf.
 * An error occurs if the PRNG has not been seeded with enough randomness to ensure an unpredictable byte sequence.
 * RAND_bytes() returns 1 on success, 0 otherwise.
 */
int RAND_bytes(unsigned char *buf, int num) {
    // https://github.com/openssl/openssl/blob/master/crypto/rand/rand_lib.c#L373
    if (num < 0) return 0;
    assert(AWS_MEM_IS_WRITABLE(buf, num));
    int rv;
    __CPROVER_assume(rv == 0 || rv == 1);
    return rv;
}
