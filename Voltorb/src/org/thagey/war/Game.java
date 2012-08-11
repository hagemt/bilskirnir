package org.thagey.war;

import java.util.Collections;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.NavigableMap;
import java.util.TreeMap;

public class Game {
	private static final int NUM_JOKERS = 0;
	private static final int WAR_CARDS = 2;

	private List<Player> m_players;

	private List<Player> m_winners;
	private List<Card> m_pot;

	public Game(String... playerNames) {
		// Setup player list
		m_players = new LinkedList<Player>();
		for (String name : playerNames) {
			m_players.add(new Player(name));
		}
		if (m_players.isEmpty()) {
			throw new IllegalArgumentException("invalid number of players (zero)");
		}
		// Build standard 52-card deck
		List<Card> deck = new LinkedList<Card>();
		for (Card.Suit s : Card.Suit.values()) {
			for (Card.Rank r : Card.Rank.values()) {
				if (!r.equals(Card.Rank.JOKER)) {
					deck.add(new Card(s, r));
				}
			}
		}
		// Add Jokers
		for (int i = 0; i < NUM_JOKERS; ++i) {
			deck.add(new Card(null, Card.Rank.JOKER));
		}
		// Randomize
		Collections.shuffle(deck);
		// Deal
		Iterator<Player> it = m_players.iterator();
		while (!deck.isEmpty()) {
			if (!it.hasNext()) {
				it = m_players.iterator();
			}
			it.next().draw(deck.remove(0));
		}
		// Scratch space
		m_winners = new LinkedList<Player>();
		m_pot = new LinkedList<Card>();
	}
	
	public Player winner() {
		// Base case: there may be a winner
		if (m_winners.size() < 2) {
			if (!m_winners.isEmpty()) {
				// Fetch the winner and his cards
				Player p = m_winners.remove(0);
				System.out.println(p + " won the pot. (" + m_pot.size() + " cards)");
				for (Card c : m_pot) {
					p.draw(c);
				}
				// Check to see if this player has all the cards
				if (p.handSize() == 52 + NUM_JOKERS) {
					return p;
				}
			}
			// Reset the winnings
			m_winners.addAll(m_players);
			m_pot.clear();
		}
		// Figure out the winners of this round
		TreeMap<Card, Player> round = new TreeMap<Card, Player>();
		Iterator<Player> it = m_winners.iterator();
		while (it.hasNext()) {
			Player p = it.next();
			Card c = p.play();
			if (c == null) {
				it.remove();
			} else {
				System.out.println(p + " played " + c);
				round.put(c, p);
				m_pot.add(c);
			}
		}
		// Get rid of all but ceiling
		NavigableMap<Card, Player> losers = round.headMap(round.lastKey(), false);
		for (Player p : losers.values()) {
			System.out.println(p + " is out. (" + p.handSize() + " held)");
			m_winners.remove(p);
		}
		// Add cards in for war
		if (m_winners.size() > 1) {
			it = m_winners.listIterator();
			while (it.hasNext()) {
				Player p = it.next();
				for (int i = 0; i < WAR_CARDS; ++i) {
					Card c = p.play();
					if (c == null) {
						it.remove();
						break;
					}
					m_pot.add(c);
				}
			}
		}
		// Play another round
		return winner();
	}
	
	public static void main(String... args) {
		System.out.println("Welcome to Jwar v0.1 by Tor E. Hagemann");
		System.out.println(new Game(args).winner() + " won...");
	}
}
