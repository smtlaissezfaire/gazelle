
module Gazelle
  class Parser
    def initialize(filename)
      file = expand_path(filename)
      raise(Errno::ENOENT) unless File.exists?(file)
      
      @filename = file
    end

  private

    def expand_path(filename)
      File.expand_path(filename)
    end
  end
end

require File.dirname(__FILE__) + "/../ext/gazelle/gazelle"
