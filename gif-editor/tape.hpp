
/*!
	\file

	\author Igor Mironchik (igor.mironchik at gmail dot com).

	Copyright (c) 2018 Igor Mironchik

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GIF_EDITOR_TAPE_HPP_INCLUDED
#define GIF_EDITOR_TAPE_HPP_INCLUDED

// Qt include.
#include <QWidget>
#include <QScopedPointer>


class FrameOnTape;


//
// Tape
//

class TapePrivate;

//! Tape with frames.
class Tape final
	:	public QWidget
{
	Q_OBJECT

signals:
	//! Frame clicked.
	void clicked( int idx );

public:
	Tape( QWidget * parent = nullptr );
	~Tape() noexcept override;

	//! \return Count of frames.
	int count() const;
	//! Add frame.
	void addFrame( const QImage & img );
	//! \return Frame.
	FrameOnTape * frame( int idx ) const;
	//! Remove frame.
	void removeFrame( int idx );
	//! Clear.
	void clear();

private:
	Q_DISABLE_COPY( Tape )

	QScopedPointer< TapePrivate > d;
}; // class Tape

#endif // GIF_EDITOR_TAPE_HPP_INCLUDED
