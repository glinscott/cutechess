/*
    This file is part of Cute Chess.

    Cute Chess is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Cute Chess is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Cute Chess.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PGN_DATABASE_H
#define PGN_DATABASE_H

#include <QObject>
#include <QList>
#include <QDateTime>
#include <pgngame.h>
#include <pgngameentry.h>

/*!
 * \brief PGN database
 *
 * \sa PgnGame
 * \sa PgnGameEntry
 * \sa PgnImporter
 */
class PgnDatabase : public QObject
{
	Q_OBJECT

	public:
		/*! PGN database processing error. */
		enum PgnDatabaseError
		{
			NoError,              //!< No error occured
			DatabaseModified,     //!< Database was modified externally
			DatabaseDoesNotExist, //!< Database file does not exist
			IoDeviceError,        //!< Generic I/O device error
			StreamError           //!< Error while processing the PGN data
		};

		/*!
		 * Constructs a new PgnDatabase with \a parent and \a fileName as
		 * the underlying database.
		 */
		PgnDatabase(const QString& fileName, QObject* parent = 0);

		/*! Set the game entries found in this database to \a entries. */
		void setEntries(const QList<PgnGameEntry>& entries);
		/*!
		 * Returns the list of game entries in this database.
		 *
		 * Game entries are light-weight "pointers" to the database. The game()
		 * method can be used to read the move information.
		 *
		 * \sa game()
		 */
		QList<PgnGameEntry> entries() const;

		/*! Returns the file name of this database. */
		QString fileName() const;

		/*!
		 * Returns the last recorded modification time of this database.
		 *
		 * \note This is recorded information. The underlying database file
		 * may have been modified afterwards.
		 *
		 * \sa setLastModified
		 */
		QDateTime lastModified() const;

		/*!
		 * Sets the modification time of this database.
		 *
		 * \sa lastModified
		 */
		void setLastModified(const QDateTime& lastModified);

		/*!
		 * Returns the display name of this database.
		 *
		 * \sa setDisplayName
		 */
		QString displayName() const;
		/*!
		 * Set the display name of this database to \a displayName.
		 *
		 * \note Display name is meant for GUI and should be editable by the
		 * user. When presenting PGN database information in GUI, display name
		 * should be used.
		 *
		 * \sa displayName
		 */
		void setDisplayName(const QString& displayName);

		/*!
		 * Reads \a game from the database using \a entry.
		 *
		 * \note \a game must be allocated by the caller and must not be NULL.
		 */
		PgnDatabaseError game(const PgnGameEntry& entry, PgnGame* game);

	private:
		QList<PgnGameEntry> m_entries;
		QString m_fileName;
		QDateTime m_lastModified;
		QString m_displayName;

};

#endif // PGN_DATABASE_H
