// header file
#include "TextPane.h"

// the actual text
#include "ui/widgets/items/TextItemWidget.h"

// widgets
#include <QHBoxLayout>

namespace UI
{
	class TextPanePrivate
	{
		public:
			QHBoxLayout* layout;
			TextItemWidget* text;
	};
}

using namespace UI;

TextPane::TextPane(QWidget* parent, QString text,
	QString font)
	:	Pane(parent),
		d(new TextPanePrivate)
{
	d->layout = new QHBoxLayout(this);
	d->layout->setContentsMargins(0, 0, 0, 0);
	d->text = new TextItemWidget(this, text, font);
	d->text->setAlignment(Qt::AlignCenter);
	d->layout->addWidget(d->text);
}

TextPane::~TextPane()
{
	delete d->text;
	delete d->layout;
	delete d;
}

QString TextPane::getText() const
{
	return d->text->getText();
}

QString TextPane::getFont() const
{
	return d->text->getFont();
}

Qt::Alignment TextPane::getAlignment() const
{
	return d->text->getAlignment();
}

void TextPane::setText(QString text)
{
	d->text->setText(text);
}

void TextPane::setFont(QString font)
{
	d->text->setFont(font);
}

void TextPane::setAlignment(Qt::Alignment alignment)
{
	d->text->setAlignment(alignment);
}