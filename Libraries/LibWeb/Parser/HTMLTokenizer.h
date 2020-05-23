/*
 * Copyright (c) 2020, Andreas Kling <kling@serenityos.org>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma once

#include <AK/StringView.h>
#include <AK/Types.h>
#include <LibWeb/Parser/HTMLToken.h>

#define ENUMERATE_TOKENIZER_STATES                                        \
    __ENUMERATE_TOKENIZER_STATE(Data)                                     \
    __ENUMERATE_TOKENIZER_STATE(RCDATA)                                   \
    __ENUMERATE_TOKENIZER_STATE(RAWTEXT)                                  \
    __ENUMERATE_TOKENIZER_STATE(ScriptData)                               \
    __ENUMERATE_TOKENIZER_STATE(PLAINTEXT)                                \
    __ENUMERATE_TOKENIZER_STATE(TagOpen)                                  \
    __ENUMERATE_TOKENIZER_STATE(EndTagOpen)                               \
    __ENUMERATE_TOKENIZER_STATE(TagName)                                  \
    __ENUMERATE_TOKENIZER_STATE(RCDATALessThanSign)                       \
    __ENUMERATE_TOKENIZER_STATE(RCDATAEndTagOpen)                         \
    __ENUMERATE_TOKENIZER_STATE(RCDATAEndTagName)                         \
    __ENUMERATE_TOKENIZER_STATE(RAWTEXTLessThanSign)                      \
    __ENUMERATE_TOKENIZER_STATE(RAWTEXTEndTagOpen)                        \
    __ENUMERATE_TOKENIZER_STATE(RAWTEXTEndTagName)                        \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataLessThanSign)                   \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataEndTagOpen)                     \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataEndTagName)                     \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataEscapeStart)                    \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataEscapeStartDash)                \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataEscaped)                        \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataEscapedDash)                    \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataEscapedDashDash)                \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataEscapedLessThanSign)            \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataEscapedEndTagOpen)              \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataEscapedEndTagName)              \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataDoubleEscapeStart)              \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataDoubleEscaped)                  \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataDoubleEscapedDash)              \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataDoubleEscapedDashDash)          \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataDoubleEscapedLessThanSign)      \
    __ENUMERATE_TOKENIZER_STATE(ScriptDataDoubleEscapeEnd)                \
    __ENUMERATE_TOKENIZER_STATE(BeforeAttributeName)                      \
    __ENUMERATE_TOKENIZER_STATE(AttributeName)                            \
    __ENUMERATE_TOKENIZER_STATE(AfterAttributeName)                       \
    __ENUMERATE_TOKENIZER_STATE(BeforeAttributeValue)                     \
    __ENUMERATE_TOKENIZER_STATE(AttributeValueDoubleQuoted)               \
    __ENUMERATE_TOKENIZER_STATE(AttributeValueSingleQuoted)               \
    __ENUMERATE_TOKENIZER_STATE(AttributeValueUnquoted)                   \
    __ENUMERATE_TOKENIZER_STATE(AfterAttributeValueQuoted)                \
    __ENUMERATE_TOKENIZER_STATE(SelfClosingStartTag)                      \
    __ENUMERATE_TOKENIZER_STATE(BogusComment)                             \
    __ENUMERATE_TOKENIZER_STATE(MarkupDeclarationOpen)                    \
    __ENUMERATE_TOKENIZER_STATE(CommentStart)                             \
    __ENUMERATE_TOKENIZER_STATE(CommentStartDash)                         \
    __ENUMERATE_TOKENIZER_STATE(Comment)                                  \
    __ENUMERATE_TOKENIZER_STATE(CommentLessThanSign)                      \
    __ENUMERATE_TOKENIZER_STATE(CommentLessThanSignBang)                  \
    __ENUMERATE_TOKENIZER_STATE(CommentLessThanSignBangDash)              \
    __ENUMERATE_TOKENIZER_STATE(CommentLessThanSignBangDashDash)          \
    __ENUMERATE_TOKENIZER_STATE(CommentEndDash)                           \
    __ENUMERATE_TOKENIZER_STATE(CommentEnd)                               \
    __ENUMERATE_TOKENIZER_STATE(CommentEndBang)                           \
    __ENUMERATE_TOKENIZER_STATE(DOCTYPE)                                  \
    __ENUMERATE_TOKENIZER_STATE(BeforeDOCTYPEName)                        \
    __ENUMERATE_TOKENIZER_STATE(DOCTYPEName)                              \
    __ENUMERATE_TOKENIZER_STATE(AfterDOCTYPEName)                         \
    __ENUMERATE_TOKENIZER_STATE(AfterDOCTYPEPublicKeyword)                \
    __ENUMERATE_TOKENIZER_STATE(BeforeDOCTYPEPublicIdentifier)            \
    __ENUMERATE_TOKENIZER_STATE(DOCTYPEPublicIdentifierDoubleQuoted)      \
    __ENUMERATE_TOKENIZER_STATE(DOCTYPEPublicIdentifierSingleQuoted)      \
    __ENUMERATE_TOKENIZER_STATE(AfterDOCTYPEPublicIdentifier)             \
    __ENUMERATE_TOKENIZER_STATE(BetweenDOCTYPEPublicAndSystemIdentifiers) \
    __ENUMERATE_TOKENIZER_STATE(AfterDOCTYPESystemKeyword)                \
    __ENUMERATE_TOKENIZER_STATE(BeforeDOCTYPESystemIdentifier)            \
    __ENUMERATE_TOKENIZER_STATE(DOCTYPESystemIdentifierDoubleQuoted)      \
    __ENUMERATE_TOKENIZER_STATE(DOCTYPESystemIdentifierSingleQuoted)      \
    __ENUMERATE_TOKENIZER_STATE(AfterDOCTYPESystemIdentifier)             \
    __ENUMERATE_TOKENIZER_STATE(BogusDOCTYPE)                             \
    __ENUMERATE_TOKENIZER_STATE(CDATASection)                             \
    __ENUMERATE_TOKENIZER_STATE(CDATASectionBracket)                      \
    __ENUMERATE_TOKENIZER_STATE(CDATASectionEnd)                          \
    __ENUMERATE_TOKENIZER_STATE(CharacterReference)                       \
    __ENUMERATE_TOKENIZER_STATE(NamedCharacterReference)                  \
    __ENUMERATE_TOKENIZER_STATE(AmbiguousAmpersand)                       \
    __ENUMERATE_TOKENIZER_STATE(NumericCharacterReference)                \
    __ENUMERATE_TOKENIZER_STATE(HexadecimalCharacterReferenceStart)       \
    __ENUMERATE_TOKENIZER_STATE(DecimalCharacterReferenceStart)           \
    __ENUMERATE_TOKENIZER_STATE(HexadecimalCharacterReference)            \
    __ENUMERATE_TOKENIZER_STATE(DecimalCharacterReference)                \
    __ENUMERATE_TOKENIZER_STATE(NumericCharacterReferenceEnd)

namespace Web {

class HTMLTokenizer {
public:
    explicit HTMLTokenizer(const StringView& input);

    Optional<HTMLToken> next_token();

private:
    Optional<u32> next_codepoint();
    Optional<u32> peek_codepoint(size_t offset) const;
    bool next_few_characters_are(const StringView&) const;
    void consume(const StringView&);
    void create_new_token(HTMLToken::Type);

    enum class State {
#define __ENUMERATE_TOKENIZER_STATE(state) state,
        ENUMERATE_TOKENIZER_STATES
#undef __ENUMERATE_TOKENIZER_STATE
    };

    static const char* state_name(State state)
    {
        switch (state) {
#define __ENUMERATE_TOKENIZER_STATE(state) \
    case State::state:                     \
        return #state;
            ENUMERATE_TOKENIZER_STATES
#undef __ENUMERATE_TOKENIZER_STATE
        };
        ASSERT_NOT_REACHED();
    }

    void will_switch_to(State);
    void will_reconsume_in(State);
    void flush_current_character_or_comment_if_needed();

    State m_state { State::Data };
    State m_return_state { State::Data };

    StringView m_input;
    size_t m_cursor { 0 };

    HTMLToken m_current_token;
};
}
