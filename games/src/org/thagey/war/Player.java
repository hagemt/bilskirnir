package org.thagey.war;

import java.util.LinkedList;
import java.util.List;

public class Player {
	private final String m_name;
	private List<Card> m_hand;
	
	public Player(String name) {
		m_name = name;
		m_hand = new LinkedList<Card>();
	}
	
	public int handSize() {
		return m_hand.size();
	}
	
	public boolean draw(Card c) {
		if (c == null) { return false; }
		return m_hand.add(c);
	}
	
	public Card play() {
		return m_hand.isEmpty() ? null : m_hand.remove(0);
	}
	
	@Override
	public String toString() {
		return m_name;
	}
}
