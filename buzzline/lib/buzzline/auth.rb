# Author::    Tor E Hagemann <hagemt@rpi.edu>
# Copyright:: Copyright (c) 2012 onetooneandonto

require 'rubygems'
require 'sinatra'

## Authorization

module Buzzline
	# Determine if the given label is valid
	def valid?(label)
		# Labels are valid if they're not nil or empty
		not (label.nil? or label.empty?)
	end
	module_function :valid?

	# Remember specific information about individual instances of use
	class Session
		# Create a session object for the given user
		def initialize(username)
			if not Buzzline::valid?(username) then
				raise ArgumentError, "Invalid username: #{username}"
			end
			@username, @authenticated = username, false
		end

		# Get the name of the user for whom this is a session
		def who
			@username
		end

		# Check if this user's session has been authorized
		def authorized?
			@authenticated
		end

		# Redirects users to login using Sinatra, if necessary
		def authorize!
			redirect '/login' unless authorized?
		end
	end
end

## Authorization Tests

require 'test/unit'

module Buzzline
	class TestCasesForModuleFunctions < Test::Unit::TestCase
		def test_validator
			assert_equal(Buzzline::valid?(nil), false)
			assert_equal(Buzzline::valid?(''), false)
			assert_equal(Buzzline::valid?(' '), true)
		end
	end
	class TestCasesForSession < Test::Unit::TestCase
		def setup
			assert_nothing_thrown { @matz_session = Session.new('Matz') }
		end
		def test_that_constructor_takes_one_nonempty_string
			assert_raise(ArgumentError) { Session.new }
			assert_raise(ArgumentError) { Session.new(nil) }
			assert_raise(ArgumentError) { Session.new('') }
			assert_equal(@matz_session.who, 'Matz')
		end
		def test_that_authorization_fails
			assert_equal(@matz_session.authorized?, false)
		end
	end
end
