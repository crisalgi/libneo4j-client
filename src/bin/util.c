/* vi:set ts=4 sw=4 expandtab:
 *
 * Copyright 2016, Chris Leishman (http://github.com/cleishm)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "../../config.h"
#include "util.h"
#include <assert.h>
#include <ctype.h>
#include <string.h>


char *strncpy_alloc(char **dest, size_t *cap, const char *s, size_t n)
{
    if (*cap < n+1)
    {
        char *updated = realloc(*dest, n+1);
        if (updated == NULL)
        {
            return NULL;
        }
        *dest = updated;
        *cap = n+1;
    }
    strncpy(*dest, s, n+1);
    (*dest)[n] = '\0';
    return *dest;
}


void trim_statement(const char **s, size_t *n)
{
    // Skip all whitespace lines before the statement, but not whitespace
    // at the start of the same line. This helps error position indicators from
    // Neo4j to be a little more helpful
    // (see: https://github.com/neo4j/neo4j/issues/7318).
    const char *e = *s + *n;
    for (const char *p = *s; p < e && isspace(*p); ++p)
    {
        if (*p == '\n')
        {
            *n -= ((p+1) - *s);
            *s = p+1;
        }
    }

    // trim all space (and ';') from the end
    for (--e; *n > 0 && (*e == '\0' || *e == ';' || isspace(*e));
            --e, --(*n))
        ;
}
