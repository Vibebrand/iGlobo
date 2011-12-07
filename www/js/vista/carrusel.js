Grafo.Carrusel = Ext.extend(Ext.Carousel,{
    initComponent : function() {
	this.on('beforecardswitch', this.onGraficaActiva, this );
	Grafo.Carrusel.superclass.initComponent.call(this);
    },
    onGraficaActiva :function(contenedor, newCard , oldCard){ 
	//newCard.fireEvent('activate', newCard);
	//oldCard.fireEvent('hide', oldCard);
    },
    updateCardPositions : function(animate) {
        var cards = this.items.items,
        ln = cards.length,
        cardOffset,
        i, card, el, style;
        
        // Now we loop over the items and position the active item
        // in the middle of the strip, and the two items on either
        // side to the left and right.
        for (i = 0; i < ln; i++) {
            card = cards[i];  
            
            // This means the items is within 2 cards of the active item
            if (this.isCardInRange(card)) {
                if (card.hidden) {
                    card.show();
                }
                
                el = card.el;
                style = el.dom.style;
                
                if (animate) {
                    if (card === this.layout.activeItem) {
                        el.on('webkitTransitionEnd', this.onTransitionEnd, this, {single: true});
                    }
                    style.webkitTransitionDuration = '1ms';
                }
                else {
                    style.webkitTransitionDuration = '0ms';
                }

                cardOffset = this.getCardOffset(card);
                if (this.horizontal) {
                    Ext.Element.cssTransform(el, {translate: [cardOffset, 0]});
                }
                else {
                    Ext.Element.cssTransform(el, {translate: [0, cardOffset]});
                }
            }
            else if (!card.hidden) {
                // All other items we position far away
                card.hide();
            }
        }
    }
});
Ext.reg('carrusel', Grafo.Carrusel);