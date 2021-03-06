
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

// GIF editor include.
#include "view.hpp"
#include "tape.hpp"
#include "frame.hpp"
#include "frameontape.hpp"
#include "crop.hpp"

// Qt include.
#include <QVBoxLayout>
#include <QScrollArea>


//
// ViewPrivate
//

class ViewPrivate {
public:
	ViewPrivate( View * parent )
		:	m_tape( nullptr )
		,	m_currentFrame( new Frame( QImage(), Frame::ResizeMode::FitToSize, parent ) )
		,	m_crop( nullptr )
		,	q( parent )
	{
	}

	//! Tape.
	Tape * m_tape;
	//! Current frame.
	Frame * m_currentFrame;
	//! Crop.
	CropFrame * m_crop;
	//! Parent.
	View * q;
}; // class ViewPrivate


//
// View
//

View::View( QWidget * parent )
	:	QWidget( parent )
	,	d( new ViewPrivate( this ) )
{
	QVBoxLayout * layout = new QVBoxLayout( this );
	layout->setMargin( 0 );
	layout->addWidget( d->m_currentFrame );

	QScrollArea * scroll = new QScrollArea( this );
	scroll->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOff );
	scroll->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
	scroll->setMinimumHeight( 150 );
	scroll->setMaximumHeight( 150 );
	scroll->setWidgetResizable( true );

	d->m_tape = new Tape( scroll );
	scroll->setWidget( d->m_tape );

	layout->addWidget( scroll );

	connect( d->m_tape, &Tape::currentFrameChanged,
		this, &View::frameSelected );
}

View::~View() noexcept
{
}

Tape *
View::tape() const
{
	return d->m_tape;
}

Frame *
View::currentFrame() const
{
	return d->m_currentFrame;
}

QRect
View::cropRect() const
{
	if( d->m_crop )
		return d->m_crop->cropRect();
	else
		return QRect();
}

void
View::startCrop()
{
	if( !d->m_crop )
	{
		d->m_crop = new CropFrame( d->m_currentFrame );
		d->m_crop->setGeometry( QRect( 0, 0,
			d->m_currentFrame->width(), d->m_currentFrame->height() ) );
		d->m_crop->show();
		d->m_crop->raise();
		d->m_crop->start();
	}
}

void
View::stopCrop()
{
	if( d->m_crop )
	{
		d->m_crop->stop();
		d->m_crop->deleteLater();
		d->m_crop = nullptr;
	}
}

void
View::frameSelected( int idx )
{
	if( idx >= 1 && idx <= d->m_tape->count() )
		d->m_currentFrame->setImage( d->m_tape->frame( idx )->image() );
	else
		d->m_currentFrame->setImage( QImage() );
}
