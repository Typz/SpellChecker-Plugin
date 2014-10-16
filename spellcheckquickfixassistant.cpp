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

#include <texteditor/quickfix.h>
#include <texteditor/codeassist/iassistinterface.h>
#include "spellcheckquickfixassistant.h"
#include "spellcheckercore.h"

using namespace SpellChecker;

namespace SpellChecker {
namespace Internal {

class SpellCheckQuickFixOperation : public TextEditor::QuickFixOperation
{
public:
    SpellCheckQuickFixOperation(const WordList &words, const QString &replacement);
    QString description() const QTC_OVERRIDE;
    void perform() QTC_OVERRIDE;

private:
    WordList m_words;
    QString m_replacement;
};

}
}

Internal::SpellCheckQuickFixOperation::SpellCheckQuickFixOperation(const WordList &words, const QString &replacement):
    m_words(words),
    m_replacement(replacement)
{
}

QString Internal::SpellCheckQuickFixOperation::description() const
{
    return QString(QLatin1String("Replace with '%1'")).arg(m_replacement);
}

void Internal::SpellCheckQuickFixOperation::perform()
{
    SpellCheckerCore* core = SpellCheckerCore::instance();
    if (core) {
        core->replaceWordsInCurrentEditor(m_words, m_replacement);
    }
}
//--------------------------------------------------

void SpellCheckQuickFixFactory::matchingOperations(const TextEditor::QuickFixInterface &interface, TextEditor::QuickFixOperations &result)
{
    Word word;   
    SpellCheckerCore* core = SpellCheckerCore::instance();
    if ((core) &&
            (core->isWordAtPositionMistake(interface->fileName(), interface->position(), word))) {
        WordList words;
        words.append(word);
        // collect all occurrences, with SpellCheckQuickFixOperation::getAllOccurrencesOfWord() ?
        foreach (const QString &suggestion, word.suggestions) {
            result.append(TextEditor::QuickFixOperation::Ptr(new Internal::SpellCheckQuickFixOperation(words, suggestion)));
        }
    }
}
//--------------------------------------------------

SpellCheckQuickFixAssistProcessor::SpellCheckQuickFixAssistProcessor(const TextEditor::IAssistProvider *provider):
    m_provider(provider)
{
}

const TextEditor::IAssistProvider *SpellCheckQuickFixAssistProcessor::provider() const
{
    return m_provider;
}

//--------------------------------------------------

bool SpellCheckQuickFixAssistProvider::isAsynchronous() const
{
    return false;
}

bool SpellCheckQuickFixAssistProvider::supportsEditor(Core::Id editorId) const
{
    return editorId == "CppEditor.C++Editor";
}

TextEditor::IAssistProcessor *SpellCheckQuickFixAssistProvider::createProcessor() const
{
    return new SpellCheckQuickFixAssistProcessor(this);
}

QList<TextEditor::QuickFixFactory *> SpellCheckQuickFixAssistProvider::quickFixFactories() const
{
    static SpellCheckQuickFixFactory *factory = new SpellCheckQuickFixFactory;
    return QList<TextEditor::QuickFixFactory *>() << factory;
}
//--------------------------------------------------
