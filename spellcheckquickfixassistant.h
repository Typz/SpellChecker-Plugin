/**************************************************************************
**
** Copyright (c) 2014 Carel Combrink
**
** This file is part of the SpellChecker Plugin, a Qt Creator plugin.
**
** The SpellChecker Plugin is free software: you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public License as
** published by the Free Software Foundation, either version 3 of the
** License, or (at your option) any later version.
**
** The SpellChecker Plugin is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with the SpellChecker Plugin.  If not, see <http://www.gnu.org/licenses/>.
****************************************************************************/

#ifndef SPELLCHECKER_SPELLCHECKQUICKFIXASSISTANT_H
#define SPELLCHECKER_SPELLCHECKQUICKFIXASSISTANT_H

#include <texteditor/quickfix.h>
#include <texteditor/codeassist/quickfixassistprovider.h>
#include <texteditor/codeassist/quickfixassistprocessor.h>

namespace SpellChecker {

class SpellCheckQuickFixFactory: public TextEditor::QuickFixFactory
{
public:
    void matchingOperations(const TextEditor::QuickFixInterface &interface, TextEditor::QuickFixOperations &result) QTC_OVERRIDE;
};

class SpellCheckQuickFixAssistProcessor : public TextEditor::QuickFixAssistProcessor
{
public:
    SpellCheckQuickFixAssistProcessor(const TextEditor::IAssistProvider *provider);
    const TextEditor::IAssistProvider *provider() const QTC_OVERRIDE;
    TextEditor::IAssistProposal *perform(const TextEditor::IAssistInterface *interface) QTC_OVERRIDE;
private:
    const TextEditor::IAssistProvider *m_provider;
};

class SpellCheckQuickFixAssistProvider : public TextEditor::QuickFixAssistProvider
{
public:
    bool isAsynchronous() const QTC_OVERRIDE;
    bool supportsEditor(Core::Id editorId) const QTC_OVERRIDE;
    TextEditor::IAssistProcessor *createProcessor() const QTC_OVERRIDE;
    QList<TextEditor::QuickFixFactory *> quickFixFactories() const QTC_OVERRIDE;
};

}

#endif // SPELLCHECKER_SPELLCHECKQUICKFIXASSISTANT_H
