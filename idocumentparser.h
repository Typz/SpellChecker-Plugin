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

#ifndef SPELLCHECKER_IDOCUMENTPARSER_H
#define SPELLCHECKER_IDOCUMENTPARSER_H

#include "Word.h"

#include <projectexplorer/projectexplorer.h>
#include <coreplugin/editormanager/ieditor.h>

#include <QObject>

namespace Core { class IOptionsPage; }

namespace SpellChecker {


/*! \brief The IDocumentParser class
 *
 * Parse a document and return all words that must be checked for
 * spelling mistakes.
 *
 * The document parsers must implement the functionality to check a list of files
 * as well as a single file. For the
 */
class IDocumentParser : public QObject
{
    Q_OBJECT
public:
    IDocumentParser(QObject *parent = 0);
    virtual ~IDocumentParser();
    virtual QString displayName() = 0;
    virtual Core::IOptionsPage* optionsPage() = 0;
    
protected:
    void getWordsFromSplitString(const QStringList& stringList, const Word& word, WordList& wordList);
signals:
    void spellcheckWordsParsed(const QString& fileName, const SpellChecker::WordList& wordlist);
    
public slots:
    /*! Slot that will get called when the current editor changes.
     * If the parser needs to know about the current editor, it should
     * implement this function.
     * \note Because of the Qt Signals and slots magic the implementation
     * of this slot does not have to be a slot for the function to get
     * called when the editor changes.
     * \param[in] editorFilePath File path of the current editor. This
     *      can be empty if there is no current editor. */
    virtual void setCurrentEditor(const QString& editorFilePath) { Q_UNUSED(editorFilePath) }
    /*! Slot that will get called when the active project changes.
     * The active project in Qt Creator is the current project selected as
     * the "Active Project", or otherwise referred to as the startup project.
     * \note Because of the Qt Signals and slots magic the implementation
     * of this slot does not have to be a slot for the function to get
     * called when the editor changes.
     * When the active project changes, it might be necessary to re-parse the files
     * int the current active project.
     * \param[in] activeProject Project pointer to the current Active
     *      project. */
    virtual void setActiveProject(ProjectExplorer::Project* activeProject) { Q_UNUSED(activeProject) }
};

} // namespace SpellChecker

#endif // SPELLCHECKER_IDOCUMENTPARSER_H
