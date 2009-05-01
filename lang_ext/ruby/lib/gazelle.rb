
module Gazelle
  class Parser
    def initialize(filename)
      @filename = File.expand_path(filename)
    end
  end
end

require File.dirname(__FILE__) + "/../ext/gazelle/gazelle"
